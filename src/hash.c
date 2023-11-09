#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hash.h"

typedef struct nodo {
	char *clave;
	void *valor;
	struct nodo *siguiente;
} nodo_t;

struct hash {
	nodo_t **vector;
	int cantidad;
	size_t capacidad;
};

#define FACTOR_CARGA_MAXIMO 0.7
const int CAPACIDAD_MINIMA = 3;

unsigned long funcion_de_hash(const char *string)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *string++)) {
		hash = ((hash << 5) + hash) + (unsigned long)c;
	}
	return hash;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash)
		return NULL;

	if (capacidad < CAPACIDAD_MINIMA)
		capacidad = CAPACIDAD_MINIMA;
	hash->capacidad = capacidad;
	hash->cantidad = 0;
	nodo_t **vector = calloc(hash->capacidad, sizeof(nodo_t *));
	if (!vector) {
		free(hash);
		return NULL;
	}
	hash->vector = vector;
	return hash;
}

char *copia_string(const char *s)
{
	char *p = malloc(strlen(s) + 1);
	if (!p)
		return NULL;
	strcpy(p, s);
	return p;
}

nodo_t *crear_nodo(const char *clave, void *elemento)
{
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return NULL;

	char *nuevo_valor = copia_string(clave);
	if (!nuevo_valor) {
		free(nodo);
		return NULL;
	}
	nodo->valor = elemento;
	nodo->clave = nuevo_valor;
	nodo->siguiente = NULL;
	return nodo;
}
bool funcion(const char *clave, void *valor, void *aux)
{
	hash_t *nuevo_hash = aux;

	if (hash_insertar(nuevo_hash, clave, valor, NULL) == nuevo_hash)
		return true;

	return false;
}
hash_t *rehash(hash_t *hash)
{
	hash_t *hash_nuevo = hash_crear(hash->capacidad * 2);
	if (!hash_nuevo)
		return NULL;

	hash_con_cada_clave(hash, funcion, hash_nuevo);
	hash_t aux = *hash;
	*hash = *hash_nuevo;
	*hash_nuevo = aux;
	hash_destruir(hash_nuevo);
	return hash;
}

void insertar_nodo(hash_t *hash, nodo_t *nodo)
{
	int posicion = (int)(funcion_de_hash(nodo->clave) % hash->capacidad);
	nodo->siguiente = hash->vector[posicion];
	hash->vector[posicion] = nodo;
	hash->cantidad++;
}
hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;
	float capacidad_de_carga =
		(float)(hash->cantidad) / (float)(hash->capacidad);

	if (capacidad_de_carga > FACTOR_CARGA_MAXIMO) {
		if (!rehash(hash))
			return NULL;
	}
	int posicion = (int)(funcion_de_hash(clave) % hash->capacidad);
	nodo_t *nuevo_nodo = crear_nodo(clave, elemento);
	if (!nuevo_nodo)
		return NULL;

	if (hash->vector[posicion] == NULL) {
		if (anterior)
			*anterior = NULL;
		insertar_nodo(hash, nuevo_nodo);
		return hash;
	}

	nodo_t *actual = hash->vector[posicion];
	while (actual) {
		if (strcmp(actual->clave, clave) == 0) {
			if (anterior)
				*anterior = actual->valor;
			actual->valor = elemento;
			free(nuevo_nodo->clave);
			free(nuevo_nodo);
			return hash;
		}
		actual = actual->siguiente;
	}

	if (anterior)
		*anterior = NULL;
	insertar_nodo(hash, nuevo_nodo);
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	int posicion = (int)(funcion_de_hash(clave) % hash->capacidad);
	nodo_t *actual = hash->vector[posicion];
	nodo_t *anterior = NULL;
	while (actual != NULL) {
		if (strcmp(actual->clave, clave) == 0) {
			void *elemento = actual->valor;
			if (anterior) {
				anterior->siguiente = actual->siguiente;
			} else {
				nodo_t *siguiente = actual->siguiente;
				hash->vector[posicion] = siguiente;
			}
			free(actual->clave);
			free(actual);
			hash->cantidad--;
			return elemento;
		}
		anterior = actual;
		actual = actual->siguiente;
	}

	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	int posicion = (int)(funcion_de_hash(clave) % hash->capacidad);
	nodo_t *actual = hash->vector[posicion];

	while (actual) {
		if (strcmp(actual->clave, clave) == 0) {
			return actual->valor;
		}
		actual = actual->siguiente;
	}
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return false;
	int posicion = (int)(funcion_de_hash(clave) % hash->capacidad);
	nodo_t *actual = hash->vector[posicion];

	while (actual) {
		if (strcmp(actual->clave, clave) == 0) {
			return true;
		}
		actual = actual->siguiente;
	}
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;
	return (size_t)(hash->cantidad);
}

void hash_destruir(hash_t *hash)
{
	if (!hash)
		return;

	for (int i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->vector[i];
		while (actual) {
			nodo_t *siguiente = actual->siguiente;
			free(actual->clave);
			free(actual);
			actual = siguiente;
		}
	}
	hash->cantidad = 0;
	hash->capacidad = 0;
	free(hash->vector);
	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;
	if (!destructor) {
		hash_destruir(hash);
		return;
	}
	for (int i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->vector[i];
		while (actual) {
			destructor(actual->valor);
			nodo_t *siguiente = actual->siguiente;
			free(actual->clave);
			free(actual);
			actual = siguiente;
		}
	}
	free(hash->vector);
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	size_t n = 0;
	if (!hash || !f)
		return 0;

	for (int i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->vector[i];
		bool seguir = true;
		while (actual && seguir) {
			seguir = f(actual->clave, actual->valor, aux);
			n++;
			if (!seguir)
				return n;
			actual = actual->siguiente;
		}
	}
	return n;
}

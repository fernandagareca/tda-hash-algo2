#include "pa2m.h"
#include "src/hash.h"
#include <string.h>
#include <stdio.h>

typedef struct nodo {
	char *clave;
	char *valor;
	struct nodo *siguiente;
} nodo_t;

struct hash {
	struct nodo **vector;
	int cantidad;
	size_t capacidad;
};
typedef struct elementos {
	char **vector;
	int posicion;
} elementos_t;
void pruebas_de_crear_hash()
{
	hash_t *h = hash_crear(4);
	pa2m_afirmar(h != NULL, "crear hash devuleve distinto de null");
	pa2m_afirmar(h->cantidad == 0,
		     "la cantidad en un hash recien creado es 0");
	pa2m_afirmar(h->capacidad == 4,
		     "la capacidad es la misma que se envio");

	hash_destruir(h);
}
void pruebas_de_busqueda()
{
	hash_t *h = hash_crear(4);
	void *anterior;
	hash_insertar(h, "a", "1", &anterior);
	hash_insertar(h, "b", "2", &anterior);
	hash_insertar(h, "c", "3", &anterior);
	hash_insertar(h, "d", "4", &anterior);
	hash_insertar(h, "e", "5", &anterior);
	hash_insertar(h, "f", "6", &anterior);

	char *vector[] = { "a", "b", "c", "d", "e", "f" };
	pa2m_afirmar(hash_cantidad(h) == 6,
		     "la cantidad de elementos insertados es 6");
	for (int i = 0; i < h->cantidad; i++) {
		pa2m_afirmar(hash_contiene(h, vector[i]) == true,
			     "valor correcto");
	}
	hash_destruir(h);
}

bool f(const char *clave, void *valor, void *aux)
{
	if (clave)
		return true;
	return false;
}

void pruebas_de_iterar_todo()
{
	hash_t *hash = hash_crear(4);
	void *anterior;
	hash_insertar(hash, "a", "1", &anterior);
	hash_insertar(hash, "b", "2", &anterior);
	hash_insertar(hash, "c", "3", &anterior);
	hash_insertar(hash, "d", "4", &anterior);
	hash_insertar(hash, "e", "5", &anterior);
	hash_insertar(hash, "f", "6", &anterior);

	char *vector[] = { "1", "2", "3", "4", "5", "6" };
	elementos_t elementos;
	elementos.vector = vector;
	elementos.posicion = 0;
	pa2m_afirmar(hash_cantidad(hash) == 6,
		     "la cantidad de elementos insertados es 6");
	pa2m_afirmar(hash_con_cada_clave(hash, f, &elementos) == 6,
		     "la cantidad de elementos iterados es 6");
	hash_destruir(hash);
}

bool funcion_aux(const char *clave, void *valor, void *aux)
{
	elementos_t *elementos = aux;

	if (elementos->posicion > 3)
		return false;

	elementos->posicion++;
	return true;
}

void pruebas_de_iterar_mitad_de_elementos()
{
	hash_t *hash = hash_crear(4);
	void *anterior;
	hash_insertar(hash, "a", "1", &anterior);
	hash_insertar(hash, "b", "2", &anterior);
	hash_insertar(hash, "c", "3", &anterior);
	hash_insertar(hash, "d", "4", &anterior);
	hash_insertar(hash, "e", "5", &anterior);
	hash_insertar(hash, "f", "6", &anterior);

	char *vector[] = { "a", "b", "c", "d", "e", "f" };
	elementos_t elementos;
	elementos.vector = vector;
	elementos.posicion = 2;
	pa2m_afirmar(hash_cantidad(hash) == 6,
		     "la cantidad de elementos insertados es 6");
	pa2m_afirmar(hash_con_cada_clave(hash, funcion_aux, &elementos) == 3,
		     "la cantidad de elementos iterados es 3");
	hash_destruir(hash);
}

void pruebas_de_insercion()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "a";
	char *clave2 = "b";
	char *clave3 = "c";
	char *clave4 = "d";
	int valor1 = 1, valor2 = 2, valor3 = 3, valor4 = 4, valor5 = 5;
	void *anterior1;
	void *anterior2;
	void *anterior3;
	void *anterior4;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &anterior1) == hash,
		     "se inserto <a,1> ");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &anterior2) == hash,
		     "se inserto <b,2> ");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &anterior3) == hash,
		     "se inserto <c,3> ");
	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, &anterior4) == hash,
		     "se inserto <d,4> ");
	int *elemento = hash_obtener(hash, clave1);
	pa2m_afirmar(*elemento == valor1, "obtengo el elemento <a,1>");
	elemento = hash_obtener(hash, clave2);
	pa2m_afirmar(*elemento == valor2, "obtengo el elemento <b,2>");
	elemento = hash_obtener(hash, clave3);
	pa2m_afirmar(*elemento == valor3, "obtengo el elemento <c,3>");
	elemento = hash_obtener(hash, clave4);
	pa2m_afirmar(*elemento == valor4, "obtengo el elemento <d,4>");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "la cantidad de elementos insertados es 4");
	pa2m_afirmar(hash_insertar(hash, clave1, &valor5, &anterior1) == hash,
		     "se inserto clave repetida <a,5>");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor5, &anterior2) == hash,
		     "se inserto clave  <b,5>");
	pa2m_afirmar(hash_cantidad(hash) == 4, "la cantidad de elementos es 4");

	hash_destruir(hash);
}

void pruebas_de_insercion_repetidos()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "a";
	char *clave2 = "b";
	char *clave3 = "c";
	char *clave4 = "d";
	int valor1 = 1, valor2 = 2, valor3 = 3, valor4 = 4;
	void *anterior1;
	void *anterior2;
	void *anterior3;
	void *anterior4;
	int nuevo_valor1 = 33;

	pa2m_afirmar(hash_insertar(hash, clave1, &valor1, &anterior1) == hash,
		     "se inserto <a,1> devuelve el hash");
	pa2m_afirmar(hash_insertar(hash, clave2, &valor2, &anterior2) == hash,
		     "se inserto <b,2> devuelve el hash");
	pa2m_afirmar(hash_insertar(hash, clave3, &valor3, &anterior3) == hash,
		     "se inserto <c,3> devuelve el hash");
	pa2m_afirmar(hash_insertar(hash, clave4, &valor4, &anterior4) == hash,
		     "se inserto <d,4> devuelve el hash");

	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "la cantidad de elementos insertados es 4");
	pa2m_afirmar(hash_insertar(hash, clave1, &nuevo_valor1, &anterior1) ==
			     hash,
		     "se inserto un valor repetido <a,33>");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "la cantidad de elementos insertados continua siendo 4");

	int *anterior = anterior1;
	pa2m_afirmar(*anterior == valor1, "anterior es 1, es correcto");
	int *valor = hash_obtener(hash, clave1);
	pa2m_afirmar(*valor == nuevo_valor1,
		     "el valor obtenido es <a,33>, es correcto");
	hash_destruir(hash);
}

void pruebas_de_insertar_muchos_elementos()
{
	hash_t *hash = hash_crear(3);
	int errores = 0;
	void *anterior;
	for (int i = 0; i < 500; i++) {
		char str[10];
		snprintf(str, sizeof(str), "%i", i);
		char *clave = str;
		if (hash_insertar(hash, clave, &i, &anterior) == NULL) {
			errores++;
		}
		if (anterior != NULL) {
			pa2m_afirmar(
				0,
				"se reemplazo valores se supone la clave es unica");
		}
	}
	pa2m_afirmar(errores == 0,
		     "se insertaron varios elementos sin problema");
	pa2m_afirmar(hash_cantidad(hash) == 500,
		     " la cantidad de elementos es 50000");
	hash_destruir(hash);
}

void pruebas_de_borrado()
{
	hash_t *hash = hash_crear(5);

	int errores = 0;
	void *anterior;
	for (int i = 0; i < 500; i++) {
		char str[10];
		snprintf(str, sizeof(str), "%i", i);
		char *clave = str;
		if (hash_insertar(hash, clave, &i, &anterior) == NULL) {
			errores++;
		}
		if (anterior != NULL) {
			pa2m_afirmar(
				0,
				"se reemplazo valores se supone la clave es unica");
		}
	}
	pa2m_afirmar(hash_cantidad(hash) == 500,
		     " la cantidad de elementos es 500");

	int obtenidos = 0;
	errores = 0;
	for (int i = 0; i < 400; i++) {
		char str[10];
		snprintf(str, sizeof(str), "%i", i);
		char *clave = str;
		void *elemento = hash_quitar(hash, clave);
		if (elemento == NULL) {
			errores++;
		}
	}
	pa2m_afirmar(hash_cantidad(hash) == 100,
		     "se elimino 1/3 de las claves");
	pa2m_afirmar(
		errores == 0,
		"se elimino varios elementos sin problema devuelve el elemento");
	pa2m_afirmar(obtenidos == 0, "ontenido dio null");
	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de creacion -----------------");
	pruebas_de_crear_hash();
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de insercion -----------------");
	pruebas_de_insercion();
	pruebas_de_insercion_repetidos();
	pruebas_de_insertar_muchos_elementos();
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de quitar -----------------");
	pruebas_de_borrado();

	pa2m_nuevo_grupo(
		"\n----------------- pruebas de busqueda -----------------");
	pruebas_de_busqueda();
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de iterador-----------------");
	pruebas_de_iterar_todo();
	pruebas_de_iterar_mitad_de_elementos();

	return pa2m_mostrar_reporte();
}

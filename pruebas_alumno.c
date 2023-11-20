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
	pa2m_afirmar(h->capacidad == 4, "la capacidad es 4 la que se envio");

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
			     "se encontro el elemento buscado");
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

void pruebas_de_insertar_clave_nula()
{
	hash_t *hash = hash_crear(4);
	void *anterior;

	pa2m_afirmar(hash_insertar(hash, NULL, "1", &anterior) == NULL,
		     "no se puede insertar con clave nula");
	pa2m_afirmar(hash_contiene(hash, NULL) == false,
		     "el elemento no se encontro en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 0, "la cantidad de clves es 0");
	hash_destruir(hash);
}

void pruebas_de_insertar_valor_nulo()
{
	hash_t *hash = hash_crear(4);
	void *anterior;

	pa2m_afirmar(hash_insertar(hash, "1", NULL, &anterior) == hash,
		     "se puede insertar con valor nula");
	pa2m_afirmar(hash_contiene(hash, "1") == true,
		     "el elemento se encontro en el hash");

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

void prueba_de_borrar()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "a";
	char *clave2 = "b";
	char *clave3 = "c";
	char *clave4 = "d";
	int valor1 = 1, valor2 = 2, valor3 = 3, valor4 = 4;

	hash_insertar(hash, clave1, &valor1, NULL);
	hash_insertar(hash, clave2, &valor2, NULL);
	hash_insertar(hash, clave3, &valor3, NULL);
	hash_insertar(hash, clave4, &valor4, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 4, "la cantidad de elementos es 4");

	int *elemento = hash_quitar(hash, clave1);
	pa2m_afirmar(*elemento == valor1, "se quito la clave 1");
	pa2m_afirmar(hash_contiene(hash, clave1) == false,
		     "el hash no contiene la clave 1");
	pa2m_afirmar(hash_cantidad(hash) == 3, "la cantidad de elementos es 3");

	elemento = hash_quitar(hash, clave2);
	pa2m_afirmar(*elemento == valor2, "se quito la clave 1");
	pa2m_afirmar(hash_contiene(hash, clave2) == false,
		     "el hash no contiene la clave 2");
	pa2m_afirmar(hash_cantidad(hash) == 2, "la cantidad de elementos es 2");

	elemento = hash_quitar(hash, clave3);
	pa2m_afirmar(*elemento == valor3, "se quito la clave 1");
	pa2m_afirmar(hash_contiene(hash, clave3) == false,
		     "el hash no contiene la clave 3");
	pa2m_afirmar(hash_cantidad(hash) == 1, "la cantidad de elementos es 1");

	elemento = hash_quitar(hash, clave4);
	pa2m_afirmar(*elemento == valor4, "se quito la clave 1");
	pa2m_afirmar(hash_contiene(hash, clave4) == false,
		     "el hash no contiene la clave 4");
	pa2m_afirmar(hash_cantidad(hash) == 0, "la cantidad de elementos es 0");

	hash_destruir(hash);
}
void pruebas_de_borrado_de_varios_elementos()
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
	pa2m_afirmar(hash_cantidad(hash) == 100, "se elimino 400 claves");
	pa2m_afirmar(errores == 0, "se elimino varios elementos sin problema");

	hash_destruir(hash);
}
void pruebas_en_un_hash_nulo()
{
	hash_t *hash = NULL;
	char *clave1 = "a";
	char *valor = "b";

	pa2m_afirmar(hash_insertar(hash, clave1, valor, NULL) == NULL,
		     "insertar en un hash nulo devuelve NULL");
	pa2m_afirmar(hash_quitar(hash, clave1) == NULL,
		     "quitar en un hash nulo devuelve NULL");
	pa2m_afirmar(hash_obtener(hash, clave1) == NULL,
		     "obtener en un hash nulo devuelve NULL");
	pa2m_afirmar(hash_con_cada_clave(hash, f, NULL) == 0,
		     "iterar en un hash nulo devuelve 0");
	pa2m_afirmar(hash_contiene(hash, clave1) == false,
		     "contiene devuelve falso si el hash es null");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "la cantidad de un hash null es 0");
}
int main()
{
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de creacion -----------------");
	pruebas_de_crear_hash();
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de insercion -----------------");
	pruebas_de_insertar_valor_nulo();
	pruebas_de_insertar_clave_nula();
	pruebas_de_insercion();
	pruebas_de_insercion_repetidos();
	pruebas_de_insertar_muchos_elementos();
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de quitar -----------------");
	prueba_de_borrar();
	pruebas_de_borrado_de_varios_elementos();

	pa2m_nuevo_grupo(
		"\n----------------- pruebas de busqueda -----------------");
	pruebas_de_busqueda();
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de iterador-----------------");
	pruebas_de_iterar_todo();
	pa2m_nuevo_grupo(
		"\n----------------- pruebas de hash null-----------------");
	pruebas_en_un_hash_nulo();

	return pa2m_mostrar_reporte();
}

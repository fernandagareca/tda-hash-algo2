<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de Marianela Fernanda Gareca Janko - 109606 - fernanda.gareca321@gmail.com

- Para compilar:

```bash
make pruebas_chanutron
```

- Para ejecutar:

```bash
./pruebas_chanutron
```

- Para ejecutar con valgrind:
```bash
make valgrind-chanutron
```
---
##  Funcionamiento

Consiste en implementar un diccionario que es una estructura que almacena elementos con clave y valor, la cual mediante la función de hash nos devuelve una posición en la tabla de hash, la cual hace más directo el acceso a la hora de buscar los elementos, reduciendo la complejidad de búsqueda o haciéndola tender a o(1) en el mejor de los casos que no hayan colisiones.


### Estructuras:




En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```

<div align="center">
<img width="70%" src="img/diagrama.jpeg">
</div>

---

## Respuestas a las preguntas teóricas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).


# diccionario
<div align="center">
<img width="70%" src="img/diccionario.jpeg">
</div>

# Metodos de resolucioon de coliciones 
<div align="center">
<img width="70%" src="img/coliciones.jpeg">
</div>
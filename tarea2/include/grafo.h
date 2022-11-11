/*
  Módulo de definición de `Grafo'.

  `Grafo' representa a los grafos no dirigidos con aristas etiquetados.

  Los vértices se identifican con naturales entre 1 y un cierto número `n'
  establecido al crearlo. 

  En las funciones que tienen un parámetro `v' que es un identificador de
  vértice se asume la precondición implícita `1 <= v <= n'.

  Para cada nodo se tiene una lista de adyacencias que se representa mediante
  la estructura Lista_pares. Si el par (v, c) está en la lista de adyacencias
  de u, entonces existe una arista (u, v) de costo c.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _GRAFO_H
#define _GRAFO_H

#include "lista_pares.h"

struct rep_grafo; // representación de `grafo', definida en `grafo.cpp'.
typedef rep_grafo *Grafo;

/* Devuelve un grafo vacío (sin aristas ni vértices) que tiene `n' vértices. */
Grafo crear_grafo(nat n);

/* Devuelve una copia de `g'.
   El grafo devuelto no comparte memoria con `g'. */
Grafo copia_grafo(Grafo g);

/* Devuelve la cantidad de vértices de `g'. */
nat cantidad_vertices(Grafo g);

/* Agrega una arista desde `v1' hacia `v2' con etiqueta `valor'.
   Si ya había una ariste desde `v1' hacia `v2' no se hace nada. */
void agregar_arista(nat v1, nat v2, nat valor, Grafo g, bool dirigido);

/* Remueve la arista desde `v1' hacia `v2'.
    Si no había una ariste desde `v1' hacia `v2' no se hace nada.
    Precondición: existe_vertice(v1, g) && existe_vertice(v2, g). */
void remover_arista(nat v1, nat v2, Grafo g);

/* Devuelve `true' si y sólo si hay una arista desde `v1' hacia `v2'. */
bool existe_arista(nat v1, nat v2, Grafo g);

/* Devuelve la cantidad de aristas de `g'. */
nat cantidad_aristas(Grafo g);

/* Devuelve una lista con los aristas que inciden en `v'.
   La lista devuelta comparte memoria con `g'. */
Lista_pares adyacentes(nat v, Grafo g);

/* Libera la memoria asignada a `g'. */
void destruir_grafo(Grafo &g);

/* Devuelve un grafo leído desde la entrada estándar.
   En la primera línea lee el valor máximo posible de vértice y si es dirigido o
   no dirigido.
   Luego, lee el identifcador de un vértice por línea.
   Para cada vértice se lee:
   identificador: lista_de_adyacentes
   donde `lista_de_adyacentes' cumple el formato descrito en
   `leer_lista_pares'. 
   Termina leyendo una línea con "0:". */
Grafo leer_grafo();

/* Crea un grafo de prueba*/
Grafo crear_grafo_prueba();

/* Imprime `g' en la salida estándar.
   Cumple el formato de leer_grafo.
   Luego agrega una línea con la cantidad de vértices, otra con la cantidad
   de aristas y una línea para cada vértice, con la cantidad de arisrtas 
   salientes y la cantidad de aristas entrantes. */
void imprimir_grafo(Grafo g);

/* Genera un arbol con un tamaño que lee de la entrada estándar. */
Grafo generar_arbol();

/* Genera un grafo con un tamaño que lee de la entrada estándar. */
Grafo generar_grafo();

/* Devuelve el costo del grafo `g'*/
nat costo(Grafo g, bool dirigido);

#endif

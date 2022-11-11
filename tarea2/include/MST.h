

#ifndef __MST__
#define __MST__

/*
  Módulo de definición de `MST.h'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/grafo.h"
#include "../include/utils.h"

/**
 * Precondiciones:
 *  - 'G' es un grafo no dirigido, conexo, compuesto de 'n'
 *     vertices y 'm' aristas. Los vertices se numeran del 1 al n.
 *     Cada arista de 'G' tiene un peso distinto asociado, mayor a 0.
 *
 * Postcondiciones:
 *  - Devuelve el costo total de un árbol de cubrimiento mínimo de G
 *  - Devuelve en la variable mst un árbol de cubrimiento mínimo de G
 *  - El tiempo de ejecucion de Prim debe ser O(mlog(n)).
 *  - El grafo pasado como entrada NO DEBE SER MODIFICADO.
 **/

nat Prim(Grafo G, Grafo &mst);

/**
 * Precondiciones:
 *  -  'T' es un árbol de cubrimiento mínimo (MST) de G = (V,E) 
 *		grafo no dirigido conexo, donde |V| = n (1 < n) y |E| = m. 
 *		Los vertices de G se numeran de 1 a n y 
 *		cada arista tiene un costo positivo asociado distinto.
 *  -  'v' y 'w' son dos vértices que representan la arista (v,w),
 *		que no pertenece a E y `costo' su costo.
 *
 * Postcondiciones:
 *  - 'grafo_arista' retorna un MST para G'=(V,E') donde E' = E U {(v,w)}.
 *	- El tiempo de ejecución de 'grafo_arista' debe ser O(n).
 *	- El árbol dado como parámetro no debe ser modificado.
 *
 **/

Grafo grafo_arista(Grafo T, nat v, nat w, nat costo);

#endif 

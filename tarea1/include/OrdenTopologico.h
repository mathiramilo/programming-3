

#ifndef __ORDEN_TOPOLOGICO__
#define __ORDEN_TOPOLOGICO__

/*
  Módulo de definición de `OrdenTopologico.h'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "lista.h"
#include "grafo.h"

/**
 * Precondiciones:
 *  - 'G' es un grafo dirigido, no necesariamente conexo, compuesto de 'n'
 *     vertices y 'm' aristas. Los vertices se numeran del 1 al n.
 *
 * Postcondiciones:
 *  - Si 'G' es un DAG se devuelve una lista de
 *    vertices v1,...,vn que determinan un orden topológico de 'G'.
 * 	  Si 'G' no es un DAG se devuelve una lista de vertices v1,...,vk
 *    que forman un ciclo dirigido de 'G', esto es, se tiene que
 *    (v1,v2),...,(vk-1, vk) son aristas dirigidas de 'G' y v1 == vk.
 *  - El tiempo de ejecucion de OrdenTopologico debe ser O(n + m).
 *  - El grafo pasado como entrada NO DEBE SER MODIFICADO.
 **/
Lista OrdenTopologico(Grafo G);

#endif

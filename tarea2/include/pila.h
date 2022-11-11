/*
  Módulo de definición de `Pila'.

  `Pila' es una estructura lineal con comportamiento LIFO cuyos
   elementos son de tipo `Nat'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_HPP
#define _PILA_HPP

#include "utils.h"

struct rep_pila; // representación de `Pila', definida en `pila.cpp'.
typedef rep_pila *Pila;

/* Devuelve una pila vacía (sin elementos). */
Pila crear_pila();

/* Apila `elem' en `p'. */
void apilar(nat elem, Pila &p);

/* Remueve de `p' el elemento que está en la cima.
  Si es_vacia_pila(p) no hace nada. */
void desapilar(Pila &p);

/* Devuelve `true' si y sólo si `p' es vacía (no tiene elementos). */
bool es_vacia_pila(Pila p);

/* Devuelve el elemento que está en la cima de `p'.
   Precondición: ! es_vacia_pila(p). */
nat cima(Pila p);

/* Libera la memoria asignada a `p'. */
void destruir_pila(Pila &p);

#endif

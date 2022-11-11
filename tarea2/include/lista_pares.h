/*
  Módulo de definición de `Lista_pares'.

  `Lista_pares' es una estructura lineal de elementos de tipo `Par_nat'.
  El tipo Par_nat es una dupla (id, valor).


  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _LISTA_PARES_H
#define _LISTA_PARES_H

#include "utils.h"

struct Par_nat {
  nat id, valor;
}; // par de naturales

// Retrona el campo id del Par_nat p.
nat id_pn(Par_nat p);

// Retorna el campo valor del Par_nat p.
nat valor_pn(Par_nat p);

// representación de `Lista_pares`, definida en `lista_pares.cpp`.
struct rep_lista_pares; 
typedef rep_lista_pares *Lista_pares;

/* Devuelve la lista vacía (sin elementos). */
Lista_pares crear_lista_pares();

/* Devuelve una copia de `lst'.
   La lista devuelta no comparte memoria con `lst'. */
Lista_pares copia_lista_pares(Lista_pares lst);

/* Inserta `elem' al inicio de `lst'. */
void insertar_par(Par_nat elem, Lista_pares &lst);

/* Remueve de `lst' el par cuya primer componente es `id' .
   Si `idx' no es primer componente en `lst' no hace nada.*/
void remover_par(nat id, Lista_pares &lst);

/* Devuelve `true' si y sólo si `lst` es vacía (no tiene elementos). */
bool es_vacia_lista_pares(Lista_pares lst);

/* Devuelve la cantidad de elementos de lst. */
nat cantidad(Lista_pares lst);

/* Devuelve `true' si y sólo si `id' es primer componente de algún par de 
   `lst'. */
bool pertenece_a_lista_pares(nat id, Lista_pares lst);

/* Devuelve el primer elemento de `lst'.
   Precondición: ! es_vacia_lista(lst). */
Par_nat primer_par(Lista_pares lst);

/* Devuelve el resto de `lst'.
   Precondición: ! es_vacia_lista(lst). */
Lista_pares resto_pares(Lista_pares lst);

/* Libera la memoria asignada a `lst'. */
void destruir_lista_pares(Lista_pares &lst);

/* Lee una lista pares desde la entrada estandar en el formato
* elem1 pVal1 elem2 pVal2 ... '.'
*/
Lista_pares leer_lista_pares();

/* Imprime `lst' en la salida estándar.
   Cada elemento se imprime cumpliendo el formato descrito en
   `imprimir_par_nat'. Después de cada elemento se imprime un espacio en
   blanco.
   Al final se imprime un punto. */
void imprimir_lista_pares(Lista_pares lst);

/* Imprime `lst' en la salida estándar, ordenada de forma creciente por valor.
   Cada elemento se imprime cumpliendo el formato descrito en
   `imprimir_par_nat'. Después de cada elemento se imprime un espacio en
   blanco.
   Al final se imprime un punto. */
void imprimir_lista_pares_ordenada(Lista_pares lst);

#endif

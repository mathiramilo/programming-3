/*
  Módulo de definición de `utils'.

  Se define tipos para los naturales, pares de naturales, y para las
  comparaciones.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _UTILS_HPP
#define _UTILS_HPP

enum Comparacion { Menor, Igual, Mayor };

/* Devuelve `<`, '=' o `>`  si `comp' es `Menor', `Igual'  o `Mayor'
  respectivamente. */
char comp_a_char(const Comparacion comp);

/* Devuelve la conversión de `op' en Comparacion.
   Precondición: `op` es `<`, `=` o `>`. */
Comparacion char_a_comp(char op);

typedef unsigned int nat; // naturales

struct Par_nat {
  nat uno, dos;
}; // par de naturales

/* Imprime `par' en la salida estándar. Se imprime entre paréntesis y los dos
elementos separados por una coma.
Ejemplo:
(2,9) */
void imprimir_par(Par_nat par);

#endif

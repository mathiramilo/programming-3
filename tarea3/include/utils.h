/*
  Módulo de definición de `utils'.

  Se define tipos para los naturales y matriz de naturales.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _UTILS_HPP
#define _UTILS_HPP

//Definicion de los numeros naturales
typedef unsigned int nat;

//Definicion de matriz de naturales
typedef nat** matriz_t;

// Crea y retorna una matriz de tamano n x m.
matriz_t crear_matriz(nat n, nat m);

// Libera la memoria de la matriz M de tamano n x m.
void destruir_matriz(matriz_t M, nat n, nat m);

#endif

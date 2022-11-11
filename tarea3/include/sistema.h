

#ifndef __sistema__
#define __sistema__

/*
  Módulo de definición de `sistema.h'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/lista.h"
#include "../include/utils.h"

/**
 * Precondiciones:
 *  - 'datos' es un arreglo de tamano n+1 con elementos de tipo nat, 
 *	  donde datos[i] es la cantidad de datos disponibles para procesar
 *	  en el día i, para todo i de 1 a n.
 *  - 'rendimiento' es un arreglo de tamano n+1 con elementos de tipo nat, 
 *	  donde rendimiento[j] es la capacidad de procesamiento del sistema
 *	  j días después del último reinicio, para todo j de 1 a n.
 *
 * Postcondiciones:
 *  - Retorna una matriz 'OPT' de tamano (n+1) x (n+1), donde OPT[i,j]
 *    es la cantidad máxima de terabytes que puede procesar el
 *    sistema entre el día i inclusive y el día n inclusive, 
 *    habiendo reiniciado el sistema por última vez en el día i-j.
 *	  Si i<j (diagonal superior de la matriz) definimos OPT[i,j] = 0.
 *  - El tiempo de ejecucion debe ser O(n^2).
 **/

matriz_t max_datos_procesados(nat n, nat* datos, nat* rendimiento);

/**
 * Precondiciones:
 *  - 'OPT' es una matriz de tamaño (n+1) x (n+1), donde OPT[i,j] es
 *    la cantidad máxima de terabytes que puede procesar el
 *    sistema entre el día i inclusive y el día n inclusive, 
 *    habiendo reiniciado el sistema por última vez en el día i-j.
 *    Si i<j (diagonal superior de la matriz) OPT[i,j] = 0.
 *	 
 * Postcondiciones:
 *  - Retorna una lista que contiene los días del 1 al n en los 
 *    que se debe reiniciar el sistema para maximizar la cantidad 
 *    total de terabytes procesados según los valores de OPT. 
 *	- El tiempo de ejecucion debe ser O(n^2).
 *
 **/

Lista planificacion_optima(nat n, matriz_t OPT);

#endif 

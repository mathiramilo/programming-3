/*
  Módulo de implementación de `utils'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"


matriz_t crear_matriz(nat n, nat m) {
  nat** M = new nat*[n];
  for (nat i = 0; i < n; i++)
    M[i] = new nat[m];
  return M;
}

void destruir_matriz(matriz_t M, nat n, nat m) {
  for (nat i = 0; i < n; i++) 
    delete[] M[i];
  delete [] M;
}


/*
  Módulo de implementación de `TColaDePrioridad`.


  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/cola_de_prioridad.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct repCP {
  nat cantidad;
  nat N;

  // arreglo de 1 .. N con los valores de prioridad y las referencias a
  // posiciones
  Par_nat *heap;

  // arreglo de 1 .. N. Determina la posición en el heap,
  // en el rango 1 .. N, de cada elemento, o 0 si
  // no está el elemento.
  nat *posiciones;
};

TColaDePrioridad crearCP(nat N) {
  TColaDePrioridad nueva = new repCP;

  nueva->cantidad = 0;
  nueva->N = N;
  nueva->heap = new Par_nat[1 + N];

  nueva->posiciones = new nat[1 + N];
  for (nat i = 1; i <= N; i++)
    nueva->posiciones[i] = 0;

  return nueva;
} // crearCP

void liberarCP(TColaDePrioridad cp) {
  delete[] cp->heap;
  delete[] cp->posiciones;
  delete cp;
} // liberarCP

nat rangoCP(TColaDePrioridad cp) { return cp->N; }

static TColaDePrioridad filtrado_ascendente(nat pos, TColaDePrioridad cp) {
  assert(pos > 0);
  assert(pos <= cp->cantidad);
  Par_nat a_mover = cp->heap[pos];
  double valor = a_mover.valor;
  while ((pos / 2 > 0) && (cp->heap[pos / 2].valor > valor)) {
    cp->heap[pos] = cp->heap[pos / 2];
    cp->posiciones[cp->heap[pos].id] = pos;
    pos = pos / 2;
  }
  cp->heap[pos] = a_mover;
  cp->posiciones[cp->heap[pos].id] = pos;
  return cp;
} // filtrado_ascendente

static TColaDePrioridad filtrado_descendente(nat pos, TColaDePrioridad cp) {
  assert(pos > 0);
  assert(pos <= cp->cantidad);
  Par_nat a_mover = cp->heap[pos];
  double valor = a_mover.valor;
  while (2 * pos <= cp->cantidad) {
    nat hijo = pos * 2;
    if ((hijo + 1 <= cp->cantidad) &&
        (cp->heap[hijo + 1].valor) < cp->heap[hijo].valor)
      hijo = hijo + 1;
    if (cp->heap[hijo].valor < valor) {
      cp->heap[pos] = cp->heap[hijo];
      cp->posiciones[cp->heap[pos].id] = pos;
      pos = hijo;
    } else {
      break;
    }
  }
  cp->heap[pos] = a_mover;
  cp->posiciones[cp->heap[pos].id] = pos;
  return cp;
} // filtrado_descendente

TColaDePrioridad insertarEnCP(nat elem, nat dist, TColaDePrioridad cp) {
  assert((1 <= elem) && (elem <= cp->N));
  assert(!estaEnCP(elem, cp));
  cp->cantidad++;
  assert(cp->cantidad <= cp->N);
  cp->heap[cp->cantidad].id = elem;
  cp->heap[cp->cantidad].valor = dist;
  cp->posiciones[elem] = cp->cantidad;
  cp = filtrado_ascendente(cp->cantidad, cp);
  return cp;
} // insertarEnCP

bool estaVaciaCP(TColaDePrioridad cp) {
  return cp->cantidad == 0;
} // estaVacioCP

Par_nat prioritario(TColaDePrioridad cp) {
  assert(!estaVaciaCP(cp));
  return cp->heap[1];
} // prioritario

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp) {
  assert(!estaVaciaCP(cp));
  cp->posiciones[cp->heap[1].id] = 0;
  cp->cantidad--;
  if (!estaVaciaCP(cp)) {
    cp->heap[1] = cp->heap[cp->cantidad + 1];
    cp->posiciones[cp->heap[1].id] = 1;
    cp = filtrado_descendente(1, cp);
  }
  return cp;
} // eliminarPrioritario

bool estaEnCP(nat v, TColaDePrioridad cp) {
  return (1 <= v) && (v <= cp->N) && cp->posiciones[v] != 0;
} // estaEnCP

nat prioridad(nat elem, TColaDePrioridad cp) {
  assert(estaEnCP(elem, cp));
  return cp->heap[cp->posiciones[elem]].valor;
} // prioridad

TColaDePrioridad actualizarEnCP(nat elem, nat dist, TColaDePrioridad cp) {
  assert(estaEnCP(elem, cp));
  double anterior = prioridad(elem, cp);
  cp->heap[cp->posiciones[elem]].valor = dist;
  if (dist < anterior)
    cp = filtrado_ascendente(cp->posiciones[elem], cp);
  else if (dist > anterior)
    cp = filtrado_descendente(cp->posiciones[elem], cp);
  return cp;
} // actualizarEnCP

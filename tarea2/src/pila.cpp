/*
  Módulo de implementación de `Pila'.

  Pila de elementos de tipo Nat.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/pila.h"

#include <stddef.h>
#include <assert.h>

struct rep_pila {
  nat elem;
  rep_pila *sig;
};

Pila crear_pila() { return NULL; }

void apilar(nat elem, Pila &p) {
  Pila nuevo = new rep_pila;
  nuevo->elem = elem;
  nuevo->sig = p;
  p = nuevo;
}

void desapilar(Pila &p) {
  if (!es_vacia_pila(p)) {
    Pila aborrar = p;
    p = p->sig;
    delete aborrar;
  }
}

bool es_vacia_pila(Pila p) { return p == NULL; }

nat cima(Pila p) {
  assert(p != NULL);
  return p->elem;
}

void destruir_pila(Pila &p) {
  while (p != NULL) {
    Pila aborrar = p;
    p = p->sig;
    delete aborrar;
  }
}

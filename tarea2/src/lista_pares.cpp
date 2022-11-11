/*
  Módulo de implementación de `lista_pares'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/lista_pares.h"
#include "../include/cola_de_prioridad.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

nat id_pn(Par_nat p) { return p.id; };

nat valor_pn(Par_nat p) { return p.valor; };

struct rep_lista_pares {
  Par_nat elem;
  rep_lista_pares *sig;
};

Lista_pares crear_lista_pares() { return NULL; }

void insertar_par(Par_nat elem, Lista_pares &lst) {
  rep_lista_pares *nuevo = new rep_lista_pares;
  nuevo->elem = elem;
  nuevo->sig = lst;
  lst = nuevo;
}

void remover_par(nat id, Lista_pares &lst) {
  if ((lst != NULL) && (id == lst->elem.id)) {
    rep_lista_pares *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  } else if (lst != NULL) {
    rep_lista_pares *cursor = lst;
    while ((cursor->sig != NULL) && (id != cursor->sig->elem.id)) {
      cursor = cursor->sig;
    }
    if (cursor->sig != NULL) {
      rep_lista_pares *aborrar = cursor->sig;
      cursor->sig = cursor->sig->sig;
      delete aborrar;
    } // else no está elem en lst, no se hace nada
  } // else lst == NULL, no se hace nada
}

Lista_pares copia_lista_pares(Lista_pares lst) {
  Lista_pares res;
  if (lst == NULL)
    res = NULL;
  else {
    res = new rep_lista_pares;
    rep_lista_pares * ultimo = res;
    ultimo->elem = lst->elem;
    while (lst->sig != NULL) {
      lst = lst->sig;
      ultimo->sig = new rep_lista_pares;
      ultimo = ultimo->sig;
      ultimo->elem = lst->elem;
    }
    ultimo->sig = NULL;
  }
  return res;
}

bool es_vacia_lista_pares(Lista_pares lst) { return (lst == NULL); }

bool pertenece_a_lista_pares(nat id, Lista_pares lst) {
  while ((lst != NULL) && (id != lst->elem.id)) {
    lst = lst->sig;
  }
  return (lst != NULL);
}

Par_nat primer_par(Lista_pares lst) {
  assert(!es_vacia_lista_pares(lst));
  return lst->elem;
}

Lista_pares resto_pares(Lista_pares lst) {
  assert(!es_vacia_lista_pares(lst));
  return lst->sig;
}

Lista_pares leer_lista_pares() {
  Lista_pares res = crear_lista_pares();
  char strnum1[10], strnum2[10]; // suficiente espacio para enteros de 32 bits
  int cant_scanf = scanf("%s p%s", strnum1, strnum2);
  (void)(cant_scanf); // para evitar el warning al compilar con -NDEBUG
  nat elem, peso;
  while (strcmp(strnum1, ".")) {
    elem = atoi(strnum1);
    peso = atoi(strnum2);
    //  insertar al final de la lista
    Par_nat par = {elem, peso};
    insertar_par(par, res);
    cant_scanf = scanf("%s p%s", strnum1, strnum2);
    (void)(cant_scanf);
  };
  return res;
}

void imprimir_par(Par_nat par) { printf("(%u,%u)", par.id, par.valor); }

void imprimir_lista_pares(Lista_pares lst) {
  while (!es_vacia_lista_pares(lst)) {
    imprimir_par(primer_par(lst));
    lst = resto_pares(lst);
  }
  printf(".");
}

nat cantidad(Lista_pares lst) {
  nat cant = 0;
  while (!es_vacia_lista_pares(lst)) {
    cant++;
    lst = resto_pares(lst);
  }
  return cant;
}

void swap(Par_nat* a, Par_nat* b) { 
    Par_nat t = *a; 
    *a = *b; 
    *b = t; 
} 

int partition (Par_nat arr[], int low, int high) { 
    Par_nat pivot = arr[high];
    int i = (low - 1); 
    for (int j = low; j <= high- 1; j++) {
        if (arr[j].id < pivot.id) 
        { 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]);
    return (i + 1); 
} 

void quickSort(Par_nat arr[], int low, int high) { 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
}

void imprimir_lista_pares_ordenada(Lista_pares lst) {
  Par_nat* arr = new Par_nat[cantidad(lst)];
  nat i = 0;
  while (!es_vacia_lista_pares(lst)) {
    arr[i++] = primer_par(lst);
    lst = resto_pares(lst);
  }
  quickSort(arr, 0, i-1);
  for (nat j = 0; j < i; j++)
    imprimir_par(arr[j]);
  printf(".");
  delete [] arr;
}

void destruir_lista_pares(Lista_pares &lst) {
  while (lst != NULL) {
    rep_lista_pares *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  }
  delete lst;
}

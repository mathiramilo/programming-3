/*
  Módulo de implementación de `Grafo'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/lista_pares.h"
#include "../include/grafo.h"
#include "../include/pila.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctime>


typedef struct vertice_t {
  Lista_pares adyacentes;
  // otros datos
} * Vertice;

struct rep_grafo {
  vertice_t *vertices; // arreglo 
  nat n;               // cantidad de vértices
  nat m;               // cantidad de aristas
};

Grafo crear_grafo(nat n) {
  Grafo g = new rep_grafo;
  g->n = n;
  g->m = 0;
  g->vertices = new vertice_t[n + 1]; // se va a ignorar la celda 0
  for (nat i = 1; i <= n; i++)
    g->vertices[i].adyacentes = crear_lista_pares();
  return g;
}

nat cantidad_vertices(Grafo g) { return g->n; }

Grafo copia_grafo(Grafo g) {
  Grafo copia = crear_grafo(g->n);
  copia->m = g->m;
  for (nat i = 1; i <= g->n; i++)
      copia->vertices[i].adyacentes = copia_lista_pares(g->vertices[i].adyacentes);
  return copia;
}

void agregar_arista(nat v1, nat v2, nat valor, Grafo g, bool dirigido) {
  assert(1 <= v1); assert(1 <= v2); assert(v1 <= g->n); assert(v2 <= g->n); 
  //assert(!pertenece_a_lista_pares(v2, g->vertices[v1].adyacentes));
  if (!pertenece_a_lista_pares(v2, g->vertices[v1].adyacentes)) {
    g->m++;
    Par_nat arista;
    arista.valor = valor;
    arista.id = v2;
    insertar_par(arista, g->vertices[v1].adyacentes);
    if (!dirigido) {
      arista.id = v1;
      insertar_par(arista, g->vertices[v2].adyacentes);
    }
  }
}

void remover_arista(nat v1, nat v2, Grafo g) {
  if (existe_arista(v1, v2, g)) {
    g->m--;
    remover_par(v2, g->vertices[v1].adyacentes);
    remover_par(v1, g->vertices[v2].adyacentes);
  }
}

bool existe_arista(nat v1, nat v2, Grafo g) {
  assert(1 <= v1); assert(1 <= v2); assert(v1 <= g->n); assert(v2 <= g->n); 
  return pertenece_a_lista_pares(v2, g->vertices[v1].adyacentes);
}

nat cantidad_aristas(Grafo g) { return g->m; }

Lista_pares adyacentes(nat v, Grafo g) {
  assert(1 <= v); assert(v <= g->n);;
  return g->vertices[v].adyacentes;
}

void destruir_grafo(Grafo &g) {
  for (nat i = 1; i <= g->n; i++)
    destruir_lista_pares(g->vertices[i].adyacentes);
  delete[] g->vertices;
  delete g;
}

void imprimir_grafo(Grafo g) {
  printf("%s\n", "Imprimiendo Grafo");
  printf("Cantidad de vértices: %u\n", g->n);
  printf("Cantidad de aristas: %u\n", g->m);
  for (nat i = 1; i <= g->n; i++){
    printf("%u: ", i);
    imprimir_lista_pares_ordenada(g->vertices[i].adyacentes);
    printf("\n");
  }
}

Grafo leer_grafo() {
  nat max;
  // printf("LEYENDO GRAFO \n");
  char str_dirigido[20];
  bool dirigido = true; // de manera predeterminada es dirigido
  int cant_scanf = scanf("%u %s", &max, str_dirigido); // cota superior de los
                                                       // identificadores de
                                                       // vértice y dirigido
  assert(cant_scanf == 2);
  (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
  if (!strcmp(str_dirigido, "no-dirigido"))
    dirigido = false;

  Grafo res = crear_grafo(max);
  nat v;
  cant_scanf = scanf("%u:", &v);
  // printf("%d: \n", v);
  assert(cant_scanf == 1);
  assert(v <= max);
  // registrar vértices y guardar temporalmente las listas de adyacencia
  Lista_pares *array_temporal = new Lista_pares[max + 1];
  for (nat i = 1; i <= max; i++)
    array_temporal[i] = crear_lista_pares();

  while (v != 0) {
    // printf("Leyendo lista pares de %d \n", v);
    array_temporal[v] = leer_lista_pares();

    cant_scanf = scanf("%u:", &v);
    // printf("%d: \n", v);
    assert(cant_scanf == 1);
    assert(v <= max);
  }
  // agregar las aristas una por una y verificar que todos los destinos de
  // aristas son vértices del grafo
  for (nat i = 1; i <= max; i++) {
    // se recorre la lista que se había guardado de manera temporal
    // printf("Llenando lista %d \n", i);
    Lista_pares lst = array_temporal[i];
    while (!es_vacia_lista_pares(lst)) {
      // printf("%d p%d \n", primer_par(lst).id, primer_par(lst).valor);
      agregar_arista(i, primer_par(lst).id, primer_par(lst).valor, res, dirigido);
      lst = resto_pares(lst);
    }
    destruir_lista_pares(lst);
  }
  for (nat i = 1; i <= max; i++) {
    if (!es_vacia_lista_pares(array_temporal[i]))
      destruir_lista_pares(array_temporal[i]);
  }
  delete[] array_temporal;
  return res;
}

Grafo crear_grafo_prueba() {
  nat max;
  bool dirigido = true;
  max = 10; // cota superior de los
                                                       // identificadores de
                                                       // vértice y dirigido
  Grafo res = crear_grafo(max);
  nat v = 1;
  assert(v <= max);
  // registrar vértices y guardar temporalmente las listas de adyacencia
  Lista_pares *array_temporal = new Lista_pares[max + 1];
  for (nat i = 1; i <= max; i++)
    array_temporal[i] = crear_lista_pares();
  Par_nat par;
  par.id = 2; par.valor = 1;
  insertar_par(par, array_temporal[v]);
  par.id = 3;
  insertar_par(par, array_temporal[v]);
  par.id = 4;
  insertar_par(par, array_temporal[v]);
  par.id = 5;
  insertar_par(par, array_temporal[v]);

  // agregar las aristas una por una y verificar que todos los destinos de
  // aristas son vértices del grafo
  for (nat i = 1; i <= max; i++) {
    // se recorre la lista que se había guardado de manera temporal
    // printf("Llenando lista %d \n", i);
    Lista_pares lst = array_temporal[i];
    while (!es_vacia_lista_pares(lst)) {
      agregar_arista(i, primer_par(lst).id, primer_par(lst).valor, res, dirigido);
      lst = resto_pares(lst);
    }
    destruir_lista_pares(array_temporal[i]);
  }
  delete[] array_temporal;
  return res;
}

Grafo generar_arbol() {
  nat tamano;
  int cant_scanf = scanf("%u", &tamano);
  assert(cant_scanf == 1);
  (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
  Grafo T = crear_grafo(tamano); // creo grafo vacío

  for (nat i = 1; i < T->n; i++)
    agregar_arista(i, i+1, i, T, false);

  return T;
}

Grafo generar_grafo() {
  nat tamano;
  int cant_scanf = scanf("%u", &tamano);
  assert(cant_scanf == 1);
  (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
  Grafo g = crear_grafo(tamano); // creo grafo vacío

  for (nat i = 1; i < g->n; i++)
    agregar_arista(i, i+1, i+1, g, false);
  
  for (nat i = 1; i < (g->n)-1; i = i + 2)
    agregar_arista(i, i+2, (i+1) + g->n, g, false);

  return g;
}

nat costo(Grafo g, bool dirigido) {
  nat costo = 0;
  if (g->m != 0)
    for (nat i = 1; i <= g->n; i++) {
      Lista_pares ady = g->vertices[i].adyacentes;
      while (!es_vacia_lista_pares(ady)){
        costo += primer_par(ady).valor;
        ady = resto_pares(ady);
      }
    }
  if (!dirigido)
    costo = costo/2;
  return costo;
}
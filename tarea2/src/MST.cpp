/*56657885*/
/*
  Módulo de implementación de `MST'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/MST.h"
#include "../include/cola_de_prioridad.h"
#include "../include/pila.h"
#include "../include/lista_pares.h"
#include "../include/grafo.h"
#include <climits>
#include <stdio.h>

nat Prim(Grafo G, Grafo &mst) {
  //---Inicializamos variables a devolver---
  nat costoTotal = 0;
  mst = crear_grafo(cantidad_vertices(G));
  //---Inicializamos arreglo key[] y Cola de Prioridad "CP"---
  TColaDePrioridad CP = crearCP(cantidad_vertices(G));
  nat *key = new nat[cantidad_vertices(G) + 1];
  key[1] = 0;
  CP = insertarEnCP(1, key[1], CP);
  for (nat i = 2; i <= cantidad_vertices(G); i++) {
    key[i] = UINT_MAX;
    CP = insertarEnCP(i, key[i], CP);
  }
  //---Inicializamos arreglo visitados[]---
  bool *visitados = new bool[cantidad_vertices(G) + 1];
  for (nat j = 1; j <= cantidad_vertices(G); j++) {
    visitados[j] = false;
  }
  nat cantVisitados = 0;
  //---Inicializamos arreglo parent[]---
  nat *parent = new nat[cantidad_vertices(G) + 1];
  for (nat k = 1; k <= cantidad_vertices(G); k++) {
    parent[k] = 0;
  }
  //---COMENZAMOS LA PARTE ITERATIVA DE "Prim"---------------------------------------------------
  while (cantVisitados != cantidad_vertices(G)) {
    //---Eliminamos el elemento prioritario de "CP" y lo agregamos a "mst"---
    nat v = id_pn(prioritario(CP));
    CP = eliminarPrioritario(CP);
    visitados[v] = true;
    cantVisitados++;
    //---Buscamos y añadimos la arista (parent[v], v) y actualizamos "costoTotal"---
    if (parent[v] != 0) {
      Lista_pares adyPv = adyacentes(parent[v], G);
      while (id_pn(primer_par(adyPv)) != v) {
        adyPv = resto_pares(adyPv);
      }
      agregar_arista(parent[v], v, valor_pn(primer_par(adyPv)), mst, false);
      costoTotal = costoTotal + valor_pn(primer_par(adyPv));
    }
    //---Agregamos los costos de las aristas adyacentes de "v" a "CP"---
    Lista_pares adyV = adyacentes(v, G);
    while (adyV != NULL) {
      //---Verifico si el vertice no fue visitado en "mst"---
      if (!visitados[id_pn(primer_par(adyV))]) {
        //---Actualizamos "CP" de ser necesario---
        if (key[id_pn(primer_par(adyV))] > valor_pn(primer_par(adyV))) {
          key[id_pn(primer_par(adyV))] = valor_pn(primer_par(adyV));
          CP = actualizarEnCP(id_pn(primer_par(adyV)), key[id_pn(primer_par(adyV))], CP);
          parent[id_pn(primer_par(adyV))] = v;
        }
      }
      //---Avanzamos en "adyV"---
      adyV = resto_pares(adyV);
    }
  }
  //---FIN PARTE ITERATIVA DE "Prim"------------------------------------------------------------
  //---Liberamos memoria---
  delete[] key;
  liberarCP(CP);
  delete[] visitados;
  delete[] parent;
  
  //---Devolvemos el costo total de "mst"---
  return costoTotal;
}


Grafo grafo_arista(Grafo T, nat v, nat w, nat costo) {
  //---Inicializamos "auxC" grafo auxiliar y agregamos la arista (v,w) de costo "costo"---
  Grafo auxC = copia_grafo(T);
  agregar_arista(v, w, costo, auxC, false);
  //---Inicializamos el nuevo MST a devolver---
  Grafo nuevoMst = copia_grafo(auxC);
  //---Eliminamos de "auxC" los nodos con una sola arista adyacente---
  //---para que "auxC" sea el ciclo que se forma al agregar (v,w)---
  for (nat i = 1; i <= cantidad_vertices(T); i++) {
    if (cantidad(adyacentes(i, auxC)) == 1) {
      //---Inicializamos "ady" vertice adyacente a "i" y removemos la arista (i,ady)---
      nat ady = id_pn(primer_par(adyacentes(i, auxC)));
      remover_arista(ady, i, auxC);
      //---Recorremos los vertices adyacentes a "ady" para verificar si alguno---
      //---quedo con una sola arista adyacente (de ser asi lo borramos)---
      while (cantidad(adyacentes(ady, auxC)) == 1) {
				nat aux = id_pn(primer_par(adyacentes(ady, auxC)));
        remover_arista(ady, id_pn(primer_par(adyacentes(ady, auxC))), auxC);
        ady = aux;
      }
    }
  }
  //--- El grafo "auxC" queda formado por las aristas que forman el ciclo ---
  //--- Buscamos la arista de mayor costo del ciclo para eliminarla de "nuevoMst" ---
  nat v1 = 0;
  nat v2 = 0;
  nat maxCosto = 0;
  for (nat j = 1; j <= cantidad_vertices(T); j++) {
		Lista_pares adyJ = adyacentes(j, auxC);
    while (adyJ != NULL) {
      if (valor_pn(primer_par(adyJ)) > maxCosto) {
        v1 = j;
        v2 = id_pn(primer_par(adyJ));
        maxCosto = valor_pn(primer_par(adyJ));
      }
      adyJ = resto_pares(adyJ);
    }
  }
  remover_arista(v1, v2, nuevoMst);
  //---Liberamos memoria---
  destruir_grafo(auxC);
  //---Devolvemos el nuevo MST---
  return nuevoMst;
}

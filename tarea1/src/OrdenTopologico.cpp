/*56657885*/
/*
  Módulo de implementación de `OrdenTopologico'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/OrdenTopologico.h"
#include "../include/lista.h"
#include "../include/grafo.h"
#include "../include/utils.h"

Lista OrdenTopologico(Grafo G) {
	Grafo copia = copia_grafo(G);
	nat *verticesEntrantes = new nat[max_vertice(copia) + 1];
	Lista candidatos = crear_lista();
	for (nat i = 1; i <= max_vertice(copia); i++) {
		if (existe_vertice(i, copia)) {
			verticesEntrantes[i] = in_grado(i, copia);
			if (verticesEntrantes[i] == 0) {
				insertar_al_final(i, candidatos);
			}
		}
	}
	//--- COMIENZO BUSQUEDA ORDEN TOPOLOGICO ------------------------------------
	comienzo(candidatos);
	Lista ordenTopo = crear_lista();
	while (existe_actual(candidatos)) {
		insertar_al_final(actual(candidatos), ordenTopo);
		final(ordenTopo);
		remover_al_inicio(candidatos);
		comienzo(adyacentes(actual(ordenTopo), copia));
		while (existe_actual(adyacentes(actual(ordenTopo), copia))) {
			verticesEntrantes[actual(adyacentes(actual(ordenTopo), copia))]--;
			if (verticesEntrantes[actual(adyacentes(actual(ordenTopo), copia))] == 0) {
				insertar_al_final(actual(adyacentes(actual(ordenTopo), copia)), candidatos);
			}
			siguiente(adyacentes(actual(ordenTopo), copia));
		}
		comienzo(candidatos);
		remover_vertice(actual(ordenTopo), copia);
	}
	destruir_lista(candidatos);
	delete[] verticesEntrantes;
	//--- FINALIZA BUSQUEDA ORDEN TOPOLOGICO ------------------------------------ 
	if (cantidad_vertices(copia) == 0) {
		destruir_grafo(copia);
		return ordenTopo;
	} else { 
	//--- COMIENZA BUSQUEDA DE CICLO --------------------------------------------
		destruir_lista(ordenTopo);
		Lista ciclo = crear_lista();
		Lista CandidatosC = crear_lista();
	//Elimino los vertices que no tienen aristas salientes
		for (nat j = 1; j <= max_vertice(copia); j++) { 
			if (existe_vertice(j, copia)) {               
				if (out_grado(j, copia) == 0) {
					remover_vertice(j, copia);
				} else {
					insertar_al_final(j, CandidatosC);
				}
			}
		}
		bool loopControl = true;
		comienzo(CandidatosC);
		nat aux = actual(CandidatosC);
		comienzo(adyacentes(aux, copia));
		nat aux2 = actual(adyacentes(aux, copia));
		insertar_al_final(aux, ciclo);
	//Creo la lista ciclo
		while (loopControl) {
			if (aux2 == aux) {
				insertar_al_final(aux2, ciclo);
				loopControl = false;
			} else {
				insertar_al_final(aux2, ciclo);
			}
			if (pertenece_a_lista(aux, adyacentes(aux2, copia))) {
				insertar_al_final(aux, ciclo);
				loopControl = false;
			}
			comienzo(adyacentes(aux2, copia));
			aux2 = actual(adyacentes(aux2, copia));
		}
	//--- FINALIZA BUSQUEDA DE CICLO --------------------------------------------
		destruir_lista(CandidatosC);
		destruir_grafo(copia);
		return ciclo;
	}
}

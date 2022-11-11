
/*
  Módulo principal de la tarea 2.

Intérprete de comandos para probar los módulos.

Está definido un grafo `g'.

Cada comando tiene un nombre y una lista (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido;
- se cumplen las precondiciones de las operaciones invocadas.

Descripción de los comandos:

Fin
   Termina el programa
# comentario
   Imprime el resto de la línea.
leer_grafo
   Lee `g' siguiendo el formato de `leer_grafo' del módulo `grafo'.
destruir_estructuras
   Destruye las estructuras (liberando la memoria asignada) y las vuelve a
crear.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/grafo.h"
#include "include/MST.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_comentario,
  cmd_leer_grafo,
  cmd_leer_mst,
  cmd_prim,
  cmd_grafo_arista,
  cmd_generar_arbol,
  cmd_generar_grafo,
  cmd_costo_grafo,
  cmd_destruir_estructuras,
  no_reconocido
};
const int cant_com = no_reconocido;

struct enum_nombre_cmd {
  const enum_cmd_t enum_cmd;
  const char *nombre_cmd;
};

/*
  Asociación entre nombre de comando y enumerado.
 */
const enum_nombre_cmd cmds[] = {
    {cmd_fin, "Fin"},
    {cmd_comentario, "#"},
    {cmd_leer_grafo, "leer_grafo"},
    {cmd_leer_mst, "leer_mst"},
    {cmd_prim, "prim"},
    {cmd_grafo_arista, "grafo_arista"},
    {cmd_generar_arbol, "generar_arbol"},
    {cmd_generar_grafo, "generar_grafo"},
    {cmd_costo_grafo, "costo_grafo"},
    {cmd_destruir_estructuras, "destruir_estructuras"}};

/*
  Devuelve el identificador de comando leido desde la entrada estándar.
 */
enum_cmd_t identificador_comando() {
  enum_cmd_t res = no_reconocido;

  const int MAX_NOMBRE = 50;
  char nom_com[MAX_NOMBRE];
  int cant_scanf = scanf("%s", nom_com);
  assert(cant_scanf == 1);
  (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
  bool encontrado = false;
  int i = cmd_fin; // = 0
  while ((!encontrado) && (i < cant_com)) {
    if (0 == strcmp(nom_com, cmds[i].nombre_cmd)) {
      res = cmds[i].enum_cmd;
      encontrado = true;
    } else {
      i++;
    }
  }
  return res;
} // identificador_comando

/*
  Incrementa el contador de comandos y muestra el prompt.
 */
void mostrar_prompt(int &cont_comandos) {
  cont_comandos++;
  printf("%u>", cont_comandos);
} // mostrar_prompt


/* Devuelve en `str_numero' la conversión de ´nat' a  string. */
void nat_a_string(char *str_numero, nat nat) {
  if (nat == UINT_MAX)
    strcpy(str_numero, "NO");
  else
    sprintf(str_numero, "%u", nat);
} // nat_a_string


int main() {
  Grafo g = crear_grafo(1);
  Grafo mst = crear_grafo(1);

  const int MAX_LINEA = 100;
  char restolinea[MAX_LINEA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {

    mostrar_prompt(cont_comandos);
    enum_cmd_t enum_com = identificador_comando();

    // procesar el comando
    switch (enum_com) {
      case cmd_fin: {
        salir = true;
        printf("Fin.\n");
        break;
      }

      case cmd_comentario: {
        fgets(restolinea, MAX_LINEA, stdin);
        printf("%s", restolinea);
        ungetc('\n', stdin);
        break;
      }

      case cmd_leer_grafo: {
        if (g != NULL)
          destruir_grafo(g);
        g = leer_grafo();
        printf("El grafo leído es:\n");
        imprimir_grafo(g);
        break;
      }

      case cmd_leer_mst: {
        if (mst != NULL)
          destruir_grafo(mst);
        mst = leer_grafo();
        break;
      }

      case cmd_prim: {
        if (mst != NULL)
          destruir_grafo(mst);
        nat costo_min = Prim(g, mst);
        if (cantidad_aristas(mst) != cantidad_vertices(g) - 1) {
          printf("El grafo retornado no tiene n-1 aristas, por lo cual no es un MST. \n");
        } else {
          printf("El costo del MST es: %d, y el MST:\n", costo_min);
          imprimir_grafo(mst);
        }
        break;
      }

      case cmd_grafo_arista: {
        // ya se cargó T en mst
        nat src, dest, cost;
        scanf("%d %d %d", &src, &dest, &cost);
        Grafo t_2 = grafo_arista(mst, src, dest, cost);
        imprimir_grafo(t_2);
        destruir_grafo(t_2);
        break;
      }

      case cmd_generar_grafo: {
        if (g != NULL)
          destruir_grafo(g);
        if (mst != NULL)
          destruir_grafo(mst);

        g = generar_grafo();
        nat n = cantidad_vertices(g);
        printf("Grafo generado de tamaño %d\n", n);
        nat costo_min = Prim(g, mst);
        if (cantidad_aristas(mst) != cantidad_vertices(g) - 1) {
          printf("El grafo retornado no tiene n-1 aristas, por lo cual no es un MST.\n");
        } else {
          printf("El costo del MST es: %d\n", costo_min);
        }
        nat costo_e;
        scanf("%u", &costo_e);
        nat costo_res = costo_min;
        if (costo_e < n)
          costo_res -= (n-costo_e);

        Grafo t_2 = grafo_arista(mst, 1, n, costo_e);
        nat costo_grafo_arista = costo(t_2, false);
        printf("El costo del resultado de grafo_arista es: %d\n", costo_grafo_arista);

        if (costo_res != costo_grafo_arista)
          printf("%s\n", "El costo del resultado de grafo_arista no es mínimo.");
        destruir_grafo(t_2);
        break;
      }

      case cmd_costo_grafo: {
        nat cost = costo(g, false);
        printf("Grafo de costo %u\n", cost);
      }

      case cmd_generar_arbol: {
        if (mst != NULL)
          destruir_grafo(mst);
        mst = generar_arbol();
        nat n = cantidad_vertices(mst);
        printf("Arbol generado de tamaño %d\n", n);
        Grafo t_2 = grafo_arista(mst, 1, n, n-2);
        imprimir_grafo(t_2);
        destruir_grafo(t_2);
        break;
      }

      case cmd_destruir_estructuras: {
        destruir_grafo(g);
        g = crear_grafo(1);
        break;
      }

      default:
        printf("Comando No Reconocido.\n");
        break;
    } // switch
    fgets(restolinea, MAX_LINEA, stdin);
  } // while

  destruir_grafo(mst);
  destruir_grafo(g);
  return 0;
}

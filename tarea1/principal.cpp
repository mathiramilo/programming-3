
/*
  Módulo principal de la tarea 1.

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
orden_topologico
   Ejecuta la función `orden_topologico' del módulo `OrdenTopologico' en `g'.
destruir_estructuras
   Destruye las estructuras (liberando la memoria asignada) y las vuelve a
crear.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/grafo.h"
#include "include/OrdenTopologico.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_comentario,
  cmd_leer_grafo,
  cmd_generar_grafo,
  cmd_orden_topologico,
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
    {cmd_generar_grafo, "generar_grafo"},
    {cmd_orden_topologico, "orden_topologico"},
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
  Grafo g = crear_grafo(1, true);

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
      destruir_grafo(g);
      g = leer_grafo();
      //      imprimir_grafo(g);
      break;
    }

    case cmd_generar_grafo: {
      destruir_grafo(g);
      g = generar_grafo();
      printf("Grafo generado de tamaño %d\n", cantidad_vertices(g));
      Lista res = OrdenTopologico(g);
      if (es_orden_topologico(res, g))
        printf("Hay orden topologico \n");
      else {
        if (es_ciclo(res, g))
          printf("Hay un ciclo \n");
        else {
          printf("La lista devuelta no es ni un orden topologico ni un ciclo. \n");
          imprimir_lista(res);
        }
      }
      destruir_lista(res);
      //      imprimir_grafo(g);
      break;
    }

    case cmd_orden_topologico: {
      Lista res = OrdenTopologico(g);
      if (es_orden_topologico(res, g))
        printf("Hay orden topologico \n");
      else {
        if (es_ciclo(res, g))
          printf("Hay un ciclo \n");
        else{
          printf("La lista devuelta no es ni un orden topologico ni un ciclo. \n");
          // imprimir_lista(res); 
        }
      }
      destruir_lista(res);
      //      imprimir_grafo(g);
      break;
    }

    case cmd_destruir_estructuras: {
      destruir_grafo(g);
      g = crear_grafo(1, true);
      break;
    }

    default:
      printf("Comando No Reconocido.\n");
      break;
    } // switch
    fgets(restolinea, MAX_LINEA, stdin);
  } // while

  destruir_grafo(g);
  return 0;
}

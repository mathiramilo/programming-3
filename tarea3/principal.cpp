
/*
  Módulo principal de la tarea 3.

Intérprete de comandos para probar los módulos.

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
leer_datos
   Lee la cantidad de datos que hay disponible cada dia para ser 
   procesados por el sistema.
leer_rendimiento
  Lee la capacidad de procesamiento del sistema para cada dia desde 
  su ultimo reinicio.
max_datos_procesados
  Ejecuta el algoritmo que retorna la cantidad maxima de datos que
  es posible procesar por el sistema.
planificacion_optima
  Ejecuta el algoritmo que retorna la planificacion que establece los
  de reinicio del sistema para maximizar la cantidad de datos procesados.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/sistema.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_comentario,
  cmd_leer_datos,
  cmd_leer_rendimiento,
  cmd_max_datos_procesados,
  cmd_planificacion_optima,
  cmd_test_tiempo,
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
    {cmd_fin,                  "Fin"},
    {cmd_comentario,           "#"},
    {cmd_leer_datos,           "leer_datos"},
    {cmd_leer_rendimiento,     "leer_rendimiento"},
    {cmd_max_datos_procesados, "max_datos_procesados"},
    {cmd_planificacion_optima, "planificacion_optima"},
    {cmd_test_tiempo,          "test_tiempo"}};

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

// Devuelve un arreglo con los elementos de la lista. El indice 0 del arreglo no se usa.
nat* lst_to_array(Lista lst) {
  nat n = cantidad_elementos(lst);
  nat* array = new nat[n+1];
  comienzo(lst);
  int i = 1;
  while (existe_actual(lst)) {
    nat elem = actual(lst);
    array[i++] = elem;
    siguiente(lst);
  }
  return array;
}

// Devuelve un arreglo de booleanos de tamano n, donde unicamente los indices que pertenecen a la lista son 'true'.
bool* bool_lst_to_bool_array(Lista lst, nat n) {
  bool* array = new bool[n];
  for (nat i = 0; i < n; i++)
    array[i] = false;
  comienzo(lst);
  while (existe_actual(lst)) {
    nat i = actual(lst);
    array[i] = true;
    siguiente(lst);
  }
  return array;
}

nat cantidad_datos_procesados(nat n, nat* datos, nat* rendimiento, Lista reinicios) {
  nat TB = 0;
  bool* hay_reinicio = bool_lst_to_bool_array(reinicios, n+1);
  nat dias_desde_ult_reinicio = 1;
  for (nat dia = 1; dia < n+1; dia++) {
    if (hay_reinicio[dia]) {
      dias_desde_ult_reinicio = 1;
    }
    else {
      TB += min(datos[dia], rendimiento[dias_desde_ult_reinicio]);
      dias_desde_ult_reinicio++;
    }
  }
  delete[] hay_reinicio;
  return TB;
}

nat* generar_rendimiento(nat n) {
  nat* rendimiento = new nat[n+1];
  for (nat i = 1; i < n+1; i++) {
    rendimiento[i] = n;
  }
  return rendimiento;
}

nat* generar_datos(nat n) {
  nat* datos = new nat[n+1];
  for (nat i = 1; i < n+1; i++) {
    datos[i] = n-i+1;
  }
  return datos;
}

int main() {

  nat n = 0;
  nat* datos = NULL;
  nat* rendimiento = NULL;
  nat** OPT = NULL;

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
        //printf("%s", restolinea);
        ungetc('\n', stdin);
        break;
      }

      case cmd_leer_datos: {
        Lista lst = leer_lista();
        //borrar datos de ejecucion anterior
        if (datos != NULL)
          delete[] datos;
        if (rendimiento != NULL)
          delete[] rendimiento;
        if (OPT != NULL)
          destruir_matriz(OPT, n+1, n+1);

        n = cantidad_elementos(lst);
        datos = lst_to_array(lst);
        destruir_lista(lst);
        break;
      }

      case cmd_leer_rendimiento: {
        Lista lst = leer_lista();
        n = cantidad_elementos(lst);
        rendimiento = lst_to_array(lst);
        destruir_lista(lst);
        break;
      }

      case cmd_max_datos_procesados: {
        OPT = max_datos_procesados(n, datos, rendimiento);
        nat TB = OPT[1][1];
        printf("Max Datos Procesados: %u\n", TB);
        break;
      }

       case cmd_planificacion_optima: {
         Lista reinicios = planificacion_optima(n, OPT);
         nat TB = cantidad_datos_procesados(n, datos, rendimiento, reinicios);
         printf("Cantidad Datos Planificacion: %u\n", TB);
         destruir_lista(reinicios);
         break;
      }

      case cmd_test_tiempo:
      {
        //borrar datos de ejecucion anterior
        if (datos != NULL)
          delete[] datos;
        if (rendimiento != NULL)
          delete[] rendimiento;
        if (OPT != NULL)
          destruir_matriz(OPT, n+1, n+1);
        scanf("%d", &n); 
        datos = generar_datos(n);
        rendimiento = generar_rendimiento(n);
        OPT = max_datos_procesados(n, datos, rendimiento); 
        nat TB = OPT[1][1];
        printf("Max Datos Procesados: %u\n", TB);
        Lista reinicios = planificacion_optima(n, OPT);
        TB = cantidad_datos_procesados(n, datos, rendimiento, reinicios);
        printf("Cantidad Datos Planificacion: %u\n", TB);
        destruir_lista(reinicios);
        break;
      }

      default:
        printf("Comando No Reconocido.\n");
        break;
    } // switch
    fgets(restolinea, MAX_LINEA, stdin);
  } // while
  if (datos != NULL)
    delete [] datos;
  if (rendimiento != NULL)
    delete [] rendimiento;
  if (OPT != NULL)
   destruir_matriz(OPT, n+1, n+1); 

  return 0;
}

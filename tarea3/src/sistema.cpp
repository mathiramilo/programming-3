/*
	Módulo de implementación de `sistema'.

	Laboratorio de Programación 3.
	InCo-FIng-UDELAR
 */

#include "../include/sistema.h"
#include "../include/lista.h"
#include "../include/utils.h"

#include <math.h>

matriz_t max_datos_procesados(nat n, nat *datos, nat *rendimiento)
{
	matriz_t OPT = crear_matriz(n + 1, n + 1);
	//---Rellenamos la matriz de abajo hacia arriba y de izquiera a derecha---
	for (nat i = n; i > 0; i--)
	{
		for (nat j = 1; j <= n; j++)
		{
			//---Matriz triangular inferior---
			if (i < j)
			{
				OPT[i][j] = 0;
			}
			else
			{
				//---Si estamos en la ultima fila---
				if (i == n)
				{
					if (datos[i] < rendimiento[j])
					{
						OPT[i][j] = datos[i];
					}
					else
					{
						OPT[i][j] = rendimiento[j];
					}
					//---Si no estamos en la ultima fila---
				}
				else
				{
					nat x;
					if (datos[i] < rendimiento[j])
					{
						x = datos[i];
					}
					else
					{
						x = rendimiento[j];
					}
					OPT[i][j] = fmax(OPT[i + 1][j + 1] + x, OPT[i + 1][1]);
				}
			}
		}
	}
	return OPT;
}

Lista planificacion_optima(nat n, matriz_t OPT)
{
	Lista reinicios = crear_lista();
	nat j = 1;
	for (nat i = 1; i < n; i++)
	{
		if (OPT[i][j] == OPT[i + 1][1])
		{
			insertar_al_final(i, reinicios);
			j = 1;
		}
		else
		{
			j++;
		}
	}
	comienzo(reinicios);
	return reinicios;
}

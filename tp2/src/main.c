
#include <stdio.h>
#include "ArrayEmployees.h"
#include "utn.h"
#define ELEMENTOS_ARRAY 10


int main(void)
{
	int opcion;
	int respuesta;
	int primeraCarga = 1;
	Employee arrayEmployees[ELEMENTOS_ARRAY];
	initEmployees(arrayEmployees, ELEMENTOS_ARRAY);

	do
	{
		respuesta = getInt("Seleccione una opción\n\n1-Cargar un empleado\n2-Modificar un empleado\n3-Dar de baja un empleado\n"
				"4-Informar empleados cargados\n5-Salir\n","No es una opción válida\n",&opcion,3,5,1);
		if(!respuesta)
		{
			switch(opcion)
			{
				case 1:
					if(CargarEmpleado(arrayEmployees, ELEMENTOS_ARRAY) != 0)
					{
						printf("El empleado no fue cargado ya que no se ingresaron valores válidos\n");
					}
					else
					{
						primeraCarga = 0;
					}
					break;
				case 2:
					if(primeraCarga != 0)
					{
						printf("Debe cargar al menos un empleado antes de poder acceder a esta opción\n");
					}
					else
					{
						ModificarEmpleado(arrayEmployees, ELEMENTOS_ARRAY);
					}
					break;
				case 3:
					if(primeraCarga != 0)
					{
						printf("Debe cargar al menos un empleado antes de poder acceder a esta opción\n");
					}
					else
					{
						if(BorrarEmpleado(arrayEmployees, ELEMENTOS_ARRAY) == 0)
						{
							primeraCarga = 1;
						}
					}
					break;
				case 4:
					if(primeraCarga != 0)
					{
						printf("Debe cargar al menos un empleado antes de poder acceder a esta opción\n");
					}
					else
					{
						sortEmployees(arrayEmployees, ELEMENTOS_ARRAY, 1);
						printEmployees(arrayEmployees, ELEMENTOS_ARRAY);
					}
					break;
			}
		}
	}while(opcion!=5);

	return 0;
}

/* A falta de tiempo para terminar las cosas que faltan, las enumero:
 * Por algún motivo me recorta los nombres y apellidos ingresados, asumo que tengo algún error en mi la función getNombre que produce esto.
 * El sort sólo ordena por apellido ASC.
 * Falta documentar algunas funciones.
 */


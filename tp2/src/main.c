
#include <stdio.h>
#include "ArrayEmployees.h"
#include "utn.h"
#define ELEMENTOS_ARRAY 5


int main(void)
{
	int opcion;
	int respuesta;
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
					break;
				case 2:
					ModificarEmpleado(arrayEmployees, ELEMENTOS_ARRAY);
					break;
				case 3:
					BorrarEmpleado(arrayEmployees, ELEMENTOS_ARRAY);
					break;
				case 4:
					printEmployees(arrayEmployees, ELEMENTOS_ARRAY);
					break;
			}
		}
	}while(opcion!=5);

	return 0;
}


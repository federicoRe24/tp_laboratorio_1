#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

//Ctrl + B para buildear

int main()
{
	int opcion;
	int respuesta;
	int flagEmpleadosCargados = 0;

    LinkedList* listaEmpleados = ll_newLinkedList();

	do
	{
		respuesta = getInt("Seleccione una opción\n\n1-Cargar datos de empleados desde archivo en modo texto\n2-Cargar datos de empleados desde archivo en modo binario"
				"\n3-Dar de alta un empleado\n4-Modificar datos de un empleado\n5-Dar de baja un empleado\n6-Listar empleados\n7-Ordenar empleados\n8-Guadar datos de "
				"empleados en archivo en modo texto\n9-Guardar datos de empleados en archivo en modo binario\n10-Salir\n", "No es una opción válida\n",&opcion,3,10,1);
		if(!respuesta)
		{
			switch(opcion)
			{
				case 1:
					if(flagEmpleadosCargados == 0)
					{
						controller_loadFromText("data.csv",listaEmpleados);
						flagEmpleadosCargados = 1;
					}
					else
					{
						printf("La carga de empleados desde archivo sólo puede hacerse una vez\n");
					}
	                break;
				case 2:
					if(flagEmpleadosCargados == 0)
					{
						controller_loadFromBinary("data.bin",listaEmpleados);
						flagEmpleadosCargados = 1;
					}
					else
					{
						printf("La carga de empleados desde archivo sólo puede hacerse una vez\n");
					}
					break;
				case 3:
					if(flagEmpleadosCargados == 1)
					{
						controller_addEmployee(listaEmpleados);
					}
					else
					{
						printf("Debe realizarse la carga de empleados desde archivo para poder realizar esta acción\n");
					}
					break;
				case 4:
					if(flagEmpleadosCargados == 1)
					{
						if(controller_editEmployee(listaEmpleados) == 0)
						{
							printf("El empleado fue modificado correctamente\n");
						}
						else
						{
							printf("No se pudo modificar el empleado solicitado\n");
						}
					}
					else
					{
						printf("Debe realizarse la carga de empleados desde archivo para poder realizar esta acción\n");
					}
					break;
				case 5:
					if(flagEmpleadosCargados == 1)
					{
						if(controller_removeEmployee(listaEmpleados) == 0)
						{
							printf("El empleado fue eliminado correctamente\n");
						}
						else
						{
							printf("No se pudo eliminar el empleado solicitado\n");
						}
					}
					else
					{
						printf("Debe realizarse la carga de empleados desde archivo para poder realizar esta acción\n");
					}
					break;
				case 6:
					if(flagEmpleadosCargados == 1)
					{
						controller_ListEmployee(listaEmpleados);
					}
					else
					{
						printf("Debe realizarse la carga de empleados desde archivo para poder realizar esta acción\n");
					}
					break;
				case 7:
					if(flagEmpleadosCargados == 1)
					{
						respuesta = getInt("Seleccione una opción\n\n1-Ordenar empleados por nombre\n2-Ordenar empleados por ID\n3-Volver\n", "No es una opción válida\n",&opcion,3,3,1);
						if(!respuesta && opcion == 1)
						{
							controller_sortEmployee(listaEmpleados);
						}
						else if(!respuesta && opcion == 2)
						{
							controller_sortEmployeeById(listaEmpleados);
						}
					}
					else
					{
						printf("Debe realizarse la carga de empleados desde archivo para poder realizar esta acción\n");
					}
					break;
				case 8:
					if(flagEmpleadosCargados == 1)
					{
						controller_saveAsText("data.csv", listaEmpleados);
					}
					else
					{
						printf("Debe realizarse la carga de empleados desde archivo para poder realizar esta acción\n");
					}
					break;
				case 9:
					if(flagEmpleadosCargados == 1)
					{
						controller_saveAsBinary("data.bin", listaEmpleados);
					}
					else
					{
						printf("Debe realizarse la carga de empleados desde archivo para poder realizar esta acción\n");
					}
					break;
			}
		}
	}while(opcion!=10);

	return 0;
}



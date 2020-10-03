
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayEmployees.h"
#include "utn.h"
#define LONG_NOMBRE 50
#define SECTORES 10
#define MAX_ID 1500

static int generarIdNuevo(void);

/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int initEmployees(Employee* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			//id = -1 ?
			list[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}

/** \brief add in a existing list of employees the values received as parameters
* in the first empty position
* \param list employee*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param salary float
* \param sector int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*
*/

/*Busca el primero vacio y le carga los valores que se le pasen*/
int addEmployee(Employee* list, int len, int id, char name[],char
lastName[],float salary,int sector)
{
	int retorno = -1;
	if(	list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == TRUE)
			{
				list[i].id = id;
				strncpy(list[i].name,name,sizeof(LONG_NOMBRE));
				strncpy(list[i].lastName,lastName,sizeof(LONG_NOMBRE));
				list[i].salary = salary;
				list[i].sector = sector;
				list[i].isEmpty = FALSE;
				return 0;
			}
		}
	}
	return retorno;
}

/** \brief find an Employee by Id en returns the index position in array.
*
* \param list Employee*
* \param len int
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*
*/
int findEmployeeById(Employee* list, int len,int id)
{
	int retorno = -1;
	if(list != NULL && id > 0)
	{
		for(int i=0; i < len; i++)
		{
			if(list[i].id == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
*
* \param list Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
*/
int removeEmployee(Employee* list, int len, int id)
{
	int retorno = -1;
	if(list != NULL && id > 0)
	{
		for(int i=0; i < len; i++)
		{
			if(list[i].id == id)
			{
				list[i].id = -1;
				list[i].isEmpty = TRUE;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
*
* \param list Employee*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int sortEmployees(Employee* list, int len, int order) //Ordena solo por apellido ASC
{
	int flagSwap;
	int i;
	int contador=0;
	int retorno = -1;
	Employee buffer;

	if(list != NULL && len >= 0)
	{
		do
		{
			flagSwap=0;
			for(i=0;i<len;i++)
			{
				contador++;
				if(list[i].lastName < list[i+1].lastName)
				{
					flagSwap = 1;
					buffer = list[i];
					list[i] = list[i+1];
					list[i+1] = buffer;
				}
			}
		}while(flagSwap);
		retorno = contador;
	}
	return retorno;
}


/** \brief print the content of employees array
*
* \param list Employee*
* \param length int
* \return int
*
*/
int printEmployees(Employee* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE)
			{
				printf("Id: %d - Nombre: %s - Apellido: %s - Salario: %.2f - Sector: %d\n",list[i].id,list[i].name,
						list[i].lastName,list[i].salary,list[i].sector);
			}
		}
		retorno = 0;
	}
	return retorno;
}

int CargarEmpleado(Employee* list, int len)
{
	int resultado;
	Employee bufferEmployee;

	resultado =  getNombre("Ingrese el nombre del empleado\n", "Debe ingresar un nombre válido\n", &bufferEmployee.name,
			3, LONG_NOMBRE);

	if(resultado == -1)
		return 1;

	resultado =  getNombre("Ingrese el apellido del empleado\n", "Debe ingresar un apellido válido\n", &bufferEmployee.lastName,
			3, LONG_NOMBRE);

	if(resultado == -1)
		return 1;

	resultado = getFloat("Ingrese el salario del empleado\n", "Debe ingresar un salario válido\n",5, &bufferEmployee.salary);

	if(resultado == -1)
		return 1;

	resultado = getInt("Ingrese el sector donde trabaja el empleado\n","Ingrese un sector válido\n",&bufferEmployee.sector,3,SECTORES,1);

	if(resultado == -1)
		return 1;

	bufferEmployee.id = generarIdNuevo();

	if(addEmployee(list, len, bufferEmployee.id, bufferEmployee.name, bufferEmployee.lastName, bufferEmployee.salary, bufferEmployee.sector) == 0)
	{
		printf("El empleado fue cargado correctamente\n");
	}
	else
	{
		printf("No se pudo cargar el empleado\n");
	}

	return 0;
}

int ModificarEmpleado(Employee* list, int len)
{
	int retorno = -1;
	int opcion;
	int respuesta;
	int id;
	int posicion;
	int resultado;
	Employee bufferEmployee;

	if(getInt("Ingrese el id del empleado a modificar","Ingrese un id válido\n",&id,3,MAX_ID,1) == 0)
	{
		posicion = findEmployeeById(list,len,id);
		if(posicion != -1)
		{
			respuesta = getInt("Seleccione un valor a modificar\n\n1-Modificar nombre\n2-Modificar apellido\n3-Modificar salario\n"
					"4-modificar sector\n","No es una opción válida\n",&opcion,3,4,1);
			if(!respuesta)
			{
				switch(opcion)
				{
					case 1:
						resultado =  getNombre("Ingrese el nombre del empleado\n", "Debe ingresar un nombre válido\n", &bufferEmployee.name,
								3, LONG_NOMBRE);
						if(resultado == -1)
							return 1;
						strncpy(list[posicion].name,bufferEmployee.name,sizeof(LONG_NOMBRE));
						break;
					case 2:
						resultado =  getNombre("Ingrese el apellido del empleado\n", "Debe ingresar un apellido válido\n", &bufferEmployee.lastName,
								3, LONG_NOMBRE);
						if(resultado == -1)
							return 1;
						strncpy(list[posicion].lastName,bufferEmployee.lastName,sizeof(LONG_NOMBRE));
						break;
					case 3:
						resultado = getFloat("Ingrese el salario del empleado\n", "Debe ingresar un salario válido\n",5, &bufferEmployee.salary);
						if(resultado == -1)
							return 1;
						list[posicion].salary = bufferEmployee.salary;
						break;
					case 4:
						resultado = getInt("Ingrese el sector donde trabaja el empleado\n","Ingrese un sector válido\n",&bufferEmployee.sector,3,SECTORES,1);
						if(resultado == -1)
							return 1;
						list[posicion].sector = bufferEmployee.sector;
						break;
				}
				retorno = 0;
			}
		}
		else
		{
			printf("No se encontró ningún empleado con el id solicitado");
		}
	}
	else
	{
		printf("No se ingresó un id válido\n");
	}
	return retorno;
}

void BorrarEmpleado(Employee* list, int len)
{
	int resultado;
	int id;

	resultado = getInt("Ingrese el id del empleado a borrar\n", "Debe ingresar un id válido [0 - 1000]\n",
										   &id, 3, len-1, 1);
	if(resultado == 0)
	{
		resultado = removeEmployee(list, len, id);
		if(resultado == 0)
		{
			printf("Empleado eliminado\n");
		}
		else
		{
			printf("No se encontró un empleado con el id ingresado\n");
		}
	}
	else
	{
		printf("No se ingresó un id válido\n");
	}
}

/**
 * \Cada vez que la llamo me devuelve un ID nuevo que nunca me devolvio antes
 */

static int generarIdNuevo(void)
{
	static int id=0; //es global pero solo la funcion puede usarla

    //guardar el ultimo que asigne (ultimo que devolvi)
    //para devolver 1+
	id++;
	return id;
}



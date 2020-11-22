
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn.h"

static int generarIdNuevo(LinkedList* pArrayListEmployee);

Employee* employee_new()
{
	return (Employee*)malloc(sizeof(Employee));
}

Employee* employee_newParametrosStr(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* this = employee_new();
	if(this != NULL)
	{
		//ATOI de texto a INT
		if(employee_setId(this,atoi(idStr)) != -1 && employee_setNombre(this,nombreStr) != -1
				&& employee_setHorasTrabajadas(this,atoi(horasTrabajadasStr)) != -1 && employee_setSueldo(this,atoi(sueldoStr)) != -1)
		{
			return this;
		}
	}
	return NULL;
}

Employee* employee_newParametros(int id,char* nombre,int horasTrabajadas, int sueldo)
{
	Employee* this = employee_new();
	if(this != NULL)
	{
		if(employee_setId(this,id) != -1 && employee_setNombre(this,nombre) != -1
				&& employee_setHorasTrabajadas(this,horasTrabajadas) != -1 && employee_setSueldo(this,sueldo) != -1)
		{
			return this;
		}
	}
	return NULL;
}

// this -> contexto (a quién estás apuntando)
void employee_delete(Employee* this)
{
	free(this);
}


int employee_getId(Employee* this)
{
	if(this!=NULL)
	{
		return this->id;
	}
	return -1;
}

int employee_setId(Employee* this,int id)
{
	int retorno = -1;
	if(this!=NULL && id > 0)
	{
		this->id = id;
		retorno = 0;
	}
	return retorno;
}

char* employee_getNombre(Employee* this)
{
	if(this!=NULL)
	{
		return this->nombre;
	}
	return NULL;
}

int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this!=NULL && isValidName(nombre, LONG_NOMBRE) == 1)
	{
		strncpy(this->nombre,nombre,sizeof(this->nombre));
		retorno = 0;
	}
	return retorno;
}


int employee_getHorasTrabajadas(Employee* this)
{
	if(this!=NULL)
	{
		return this->horasTrabajadas;
	}
	return -1;
}


int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this!=NULL) // && horasTrabajadas > 0)
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}

int employee_getSueldo(Employee* this)
{
	if(this!=NULL)
	{
		return this->sueldo;
	}
	return -1;
}

int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this!=NULL) // && sueldo > 0)
	{
		this->sueldo = sueldo;
		retorno = 0;
	}
	return retorno;
}

int isValidName(char* nombre, int limite)
{
	int respuesta = 1; // TODO OK

	for(int i=0; i<=limite && nombre[i] != '\0';i++)
	{
		//esta mal <----- A - Z -----> Esta mal
		if(	(nombre[i] < 'A' || nombre[i] > 'Z') &&
			(nombre[i] < 'a' || nombre[i] > 'z') &&
			nombre[i] != '.' && nombre[i] != '-' &&
			nombre[i] != ' ')
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}

int employee_compararNombre(void* thisA,void* thisB)
{
	int retorno;
	if(thisA != NULL && thisB != NULL)
	{
		char bufferNombreA[256];
		char bufferNombreB[256];
		int respuesta;

		// Casteo el void a Employee
		//employee_getNombre((Employee*)thisA,bufferNombreA);
		//employee_getNombre((Employee*)thisB,bufferNombreB);

		strncpy(bufferNombreA, employee_getNombre((Employee*)thisA), LONG_NOMBRE);
		strncpy(bufferNombreB, employee_getNombre((Employee*)thisB), LONG_NOMBRE);

		// Devuelve positivo, negativo o 0
		respuesta = strcmp(bufferNombreA,bufferNombreB);
		if(respuesta > 0)
		{
			retorno = 1;
		}
		else if(respuesta < 0)
		{
			retorno = -1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}

int employee_compararId(void* thisA,void* thisB)
{
	int retorno;
	if(thisA != NULL && thisB != NULL)
	{
		int bufferIdA;
		int bufferIdB;

		bufferIdA = employee_getId((Employee*)thisA);
		bufferIdB = employee_getId((Employee*)thisB);

		if(bufferIdA > bufferIdB)
		{
			retorno = 1;
		}
		else if(bufferIdA > bufferIdB)
		{
			retorno = -1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}

int employee_load(int* id,char* nombre,int* horasTrabajadas, int* sueldo, LinkedList* pArrayListEmployee)
{
	int resultado;

	resultado =  getNombre("Ingrese el nombre del empleado\n", "Debe ingresar un nombre válido\n", nombre,
			3, LONG_NOMBRE);

	if(resultado == -1)
		return resultado;

	resultado = getInt("Ingrese las horas trabajadas por el empleado\n","Ingrese una cantidad de horas válida\n",horasTrabajadas,3,MAX_INT,1);

	if(resultado == -1)
		return resultado;

	resultado = getInt("Ingrese el sueldo del empleado\n", "Debe ingresar un sueldo válido\n",sueldo,3,MAX_INT,1);

	if(resultado == -1)
		return resultado;

	*id = generarIdNuevo(pArrayListEmployee);
	resultado = 0;

	return resultado;
}

/**
 * \Cada vez que la llamo busca el ID más alto que encuentre en la lista y me devuelve el próximo ó -1 si hubo error.
 */

static int generarIdNuevo(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int len;
	int max;
	Employee* bufferEmpleado;
	if(pArrayListEmployee != NULL)
	{
		len = ll_len(pArrayListEmployee);
		for(int i; i< len; i++)
		{
			bufferEmpleado = ll_get(pArrayListEmployee, i);
			retorno = employee_getId(bufferEmpleado) + 1;
			if (i == 0 || retorno > max)
			{
				max = retorno;
			}

		}
		retorno = max;
	}
	return retorno;
}

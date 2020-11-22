#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	//Recibe la lista y el puntero al archivo - Debe parsear cada linea del archivo como un empleado
	int retorno = -1;
	Employee* pBuffer;
	int retornoLectura;
	char idStr[128];
	char nombre[128];
	char horasTrabajadasStr[128];
	char sueldoStr[128];

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		retorno = 0;
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",idStr,nombre,horasTrabajadasStr,sueldoStr); // Para saltear el header
		do
		{
			// fscanf() devuelve la cantidad de variables que pudo escribir
			retornoLectura = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",idStr,nombre,horasTrabajadasStr,sueldoStr);
			if(retornoLectura == 4)
			{
				//ATOI de texto a INT
				pBuffer = employee_newParametrosStr(idStr, nombre, horasTrabajadasStr, sueldoStr);
				//printf("%s\n", pBuffer->nombre);
				ll_add(pArrayListEmployee,pBuffer);
			}
			else
			{
				employee_delete(pBuffer);
			}
		}while(!feof(pFile));
	}

    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pBuffer;
	int retornoLectura;
	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			pBuffer = employee_new();
			retornoLectura = fread(pBuffer,sizeof(Employee),1,pFile);
			if(retornoLectura == 1)
			{
				ll_add(pArrayListEmployee,pBuffer);
			}
			else
			{
				employee_delete(pBuffer);
				break;
			}
		}while(!feof(pFile));
		retorno = 0;
	}

    return retorno;
}

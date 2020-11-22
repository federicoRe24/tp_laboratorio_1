#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		FILE *pFile = fopen(path,"r");
		retorno = parser_EmployeeFromText(pFile,pArrayListEmployee);
		fclose(pFile);
	}
		return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		FILE *pFile = fopen(path,"rb");
		if(pFile != NULL)
		{
			retorno = parser_EmployeeFromBinary(pFile,pArrayListEmployee);
			fclose(pFile);
		}
	}
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(pArrayListEmployee !=NULL)
	{
		int id;
		char nombre[LONG_NOMBRE];
		int horasTrabajadas;
		int sueldo;
		if(employee_load(&id, nombre, &horasTrabajadas, &sueldo, pArrayListEmployee) == 0)
		{
			Employee* pBuffer;
			pBuffer = employee_newParametros(id, nombre, horasTrabajadas, sueldo);
			if(pBuffer != NULL)
			{
				ll_add(pArrayListEmployee,pBuffer);
				printf("El empleado fue cargado correctamente\n");
			}
			else
			{
				printf("No se pudo cargar el empleado\n");
			}
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief find an Employee by Id en returns the index position in array.
*
* \param pArrayListEmployee LinkedList*
* \param id int
* \return Return employee index position or (-1) if NULL LinkedList* or !(Id >0) or employee not found]
*
*/
int controller_findEmployeeById(LinkedList* pArrayListEmployee, int id)
{
	int retorno = -1;
	if(pArrayListEmployee != NULL && id > 0)
	{
		int len = ll_len(pArrayListEmployee);
		Employee* bufferEmpoyee;
		for(int i=0; i < len; i++)
		{
			bufferEmpoyee = ll_get(pArrayListEmployee, i);
			if(employee_getId(bufferEmpoyee) == id)
			{
				retorno = i;
			}
		}
	}
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(pArrayListEmployee != NULL)
	{
		int opcion;
		int id;
		int posicion;
		Employee* bufferEmployee;
		char nombre[LONG_NOMBRE];
		int horasTrabajadas;
		int sueldo;

		if(getInt("Ingrese el id del empleado a modificar: ","Ingrese un id válido\n",&id,3,MAX_INT,1) == 0)
		{
			posicion = controller_findEmployeeById(pArrayListEmployee, id);
			if(posicion != -1)
			{
				bufferEmployee = ll_get(pArrayListEmployee, posicion);
				retorno = getInt("Seleccione un valor a modificar\n\n1-Modificar nombre\n2-Modificar horas trabajadas\n3-Modificar sueldo\n",
						"No es una opción válida\n",&opcion,3,3,1);
				if(retorno == 0)
				{
					switch(opcion)
					{
						case 1:
							retorno =  getNombre("Ingrese el nombre del empleado\n", "Debe ingresar un nombre válido\n", nombre,
									3, LONG_NOMBRE);
							retorno = employee_setNombre(bufferEmployee, nombre);
							break;
						case 2:
							retorno = getInt("Ingrese las horas trabajadas por el empleado\n","Ingrese una cantidad de horas válida\n",&horasTrabajadas,3,MAX_INT,1);
							retorno = employee_setHorasTrabajadas(bufferEmployee, horasTrabajadas);
							break;
						case 3:
							retorno = getInt("Ingrese el sueldo del empleado\n", "Debe ingresar un sueldo válido\n",&sueldo,3,MAX_INT,1);
							retorno = employee_setSueldo(bufferEmployee, sueldo);
							break;
					}
				}
			}
		}
	}
	return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int id;
	int posicion;
	if(pArrayListEmployee)
	{
		if(getInt("Ingrese el id del empleado a eliminar: ","Ingrese un id válido\n",&id,3,MAX_INT,1) == 0)
		{
			posicion = controller_findEmployeeById(pArrayListEmployee, id);
			if(posicion != -1)
			{
				ll_remove(pArrayListEmployee, posicion);
				retorno = 0;
			}
		}
	}

    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(pArrayListEmployee != NULL)
	{
		Employee* bufferEmployee;
		for(int i=0; i< ll_len(pArrayListEmployee); i++)
		{
			bufferEmployee = (Employee*)ll_get(pArrayListEmployee, i);
			printf("Id: %d - Nombre: %s - Horas Trabajadas: %d - Sueldo: %d\n",bufferEmployee->id, bufferEmployee->nombre,
					bufferEmployee->horasTrabajadas, bufferEmployee->sueldo);
		}
		retorno = 0;
	}

    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(pArrayListEmployee != NULL)
	{
		if(pArrayListEmployee != NULL)
		{
			ll_sort(pArrayListEmployee,employee_compararNombre,1);
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief Ordenar empleados por ID
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployeeById(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(pArrayListEmployee != NULL)
	{
		if(pArrayListEmployee != NULL)
		{
			ll_sort(pArrayListEmployee,employee_compararId,1);
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		FILE *pFile;
		int len = ll_len(pArrayListEmployee);
		Employee *pEmployee;
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			retorno = 0;
			for(int i=0;i<len;i++)
			{
				pEmployee = ll_get(pArrayListEmployee,i);
				fprintf(pFile,"%d,%s,%d,%d\n",pEmployee->id,pEmployee->nombre,pEmployee->horasTrabajadas,pEmployee->sueldo);
			}
		}
		fclose(pFile);
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	if(path != NULL && pArrayListEmployee != NULL)
	{
		FILE *pFile;
		int len = ll_len(pArrayListEmployee);
		Employee *pEmployee;
		pFile = fopen(path,"wb");
		if(pFile != NULL)
		{
			retorno = 0;
			for(int i=0;i<len;i++)
			{
				pEmployee = ll_get(pArrayListEmployee,i);
				fwrite(pEmployee,sizeof(Employee),1,pFile);
			}
		}
		fclose(pFile);
	}
    return retorno;
}

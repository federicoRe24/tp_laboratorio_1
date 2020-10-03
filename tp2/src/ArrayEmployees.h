/*
 * Employee.h
 *
 *  Created on: 26 sept. 2020
 *      Author: totinho91
 */

#ifndef SRC_ARRAYEMPLOYEES_H_
#define SRC_ARRAYEMPLOYEES_H_

#define TRUE 1
#define FALSE 0
#define LONG_NOMBRE 50
//#define QTY_ALUMNOS 5
//#define MIN_LEGAJO 50
//#define MAX_LEGAJO 9999

struct
{
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int isEmpty;

}typedef Employee;

int initEmployees(Employee* list, int len);
int addEmployee(Employee* list, int len, int id, char name[],char
lastName[],float salary,int sector);
int findEmployeeById(Employee* list, int len,int id);
int removeEmployee(Employee* list, int len, int id);
int sortEmployees(Employee* list, int len, int order);
int printEmployees(Employee* list, int length);
void BorrarEmpleado(Employee* list, int len);
int CargarEmpleado(Employee* list, int len);
int ModificarEmpleado(Employee* list, int len);

#endif /* SRC_ARRAYEMPLOYEES_H_ */

#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#define LONG_NOMBRE 128
#define MAX_INT 999999
#include "LinkedList.h"

typedef struct
{
    int id;
    char nombre[LONG_NOMBRE];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametrosStr(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
Employee* employee_newParametros(int id,char* nombreStr,int horasTrabajadas, int sueldo);
void employee_delete(Employee* this);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this);

int employee_setNombre(Employee* this,char* nombre);
char* employee_getNombre(Employee* this);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this);

int employee_compararNombre(void* thisA,void* thisB);
int employee_compararId(void* thisA,void* thisB);

int isValidName(char* nombre, int limite);

int employee_load(int* id,char* nombre,int* horasTrabajadas, int* sueldo, LinkedList* pArrayListEmployee);

#endif // employee_H_INCLUDED

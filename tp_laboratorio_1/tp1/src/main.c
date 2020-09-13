
#include <stdio.h>
#include "utn.h"


int main(void){

	float numero1;
	float numero2;
	int opcion;
	int respuesta;
	float resultadoSuma;
	float resultadoResta;
	float resultadoProducto;
	float resultadoDivision;
	float resultadoFactorialUno;
	float resultadoFactorialDos;
	int exitoOperacion[6];

	do
	{
		printf("Número A: %.2f\n", numero1);
		printf("Número B: %.2f\n", numero2);
		respuesta = getInt("Seleccione una opción\n\n1-Ingresar 1er operando\n2-Ingresar 2do operando\n3-Calcular operaciones\n4-Informar resultados\n5-Salir\n",
							"No es una opción válida\n",&opcion,3,5,1);
		if(!respuesta)
		{

			switch(opcion)
			{
				case 1:
					getFloat("Ingrese el 1er operando\n", "Debe ingresar un número válido\n",5, &numero1);
					break;
				case 2:
					getFloat("Ingrese el 2do operando\n", "Debe ingresar un número válido\n",5, &numero2);
					break;
				case 3:
					exitoOperacion[0] = sumar(numero1, numero2, &resultadoSuma);
					exitoOperacion[1] = restar(numero1, numero2, &resultadoResta);
					exitoOperacion[2] = multiplicar(numero1, numero2, &resultadoProducto);
					exitoOperacion[3] = dividir(numero1, numero2, &resultadoDivision);
					exitoOperacion[4] = calcularFactorial(numero1,&resultadoFactorialUno);
					exitoOperacion[5] = calcularFactorial(numero2,&resultadoFactorialDos);
					break;
				case 4:
					informarResultados(exitoOperacion,resultadoSuma,resultadoResta,resultadoProducto,resultadoDivision,resultadoFactorialUno,resultadoFactorialDos);
					break;
			}
		}
	}while(opcion!=5);

	return 0;
}

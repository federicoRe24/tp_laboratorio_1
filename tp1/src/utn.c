
#include <stdio.h>
#include <stdio_ext.h>
#include "utn.h"

/*
* \brief - Solicita un entero al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensajeError Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int minimo, valor minimo admitido
 * \param int maximo, valor maximo admitido
 * \return (-1) Error / (0) Ok
 */

int getInt(char* mensaje, char* mensajeError, int* pResultado, int reintentos, int maximo, int minimo)
{
	int retorno = -1;
	int bufferInt; // Variable descartable
	int resultadoScanf;
	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			maximo >= minimo) // Como mínimo, que máx sea mayor que mín para que tenga sentido

	do
	{
		printf("%s", mensaje);
		__fpurge(stdin); // stdin --> standard input
		resultadoScanf = scanf("%d", &bufferInt);
		if(resultadoScanf == 1 && bufferInt >= minimo && bufferInt <= maximo)
		{
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}
		else
		{
			//Error
			printf("%s",mensajeError);
			reintentos --;
		}
	}while(reintentos >= 0);

	return retorno;
}


/*
* \brief - Solicita un float al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensajeError, Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \return (-1) Error / (0) Ok
 */


int getFloat(char *mensaje,char *mensajeError,int reintentos,float *pResultado)
{
	int retorno = -1;
	int resultadoScan;
	float bufferFloat;
	printf("%s",mensaje);
	__fpurge(stdin);
	resultadoScan = scanf("%f", &bufferFloat);
	while (resultadoScan == 0 && reintentos > 0)
	{
		reintentos--;
		printf("%s",mensajeError);
		__fpurge(stdin);
		resultadoScan = scanf("%f", &bufferFloat);
	}
	if(resultadoScan != 0)
	{ //TODO OK
		*pResultado = bufferFloat;
		retorno = 0;
	}
	return retorno;
}

/*
* \brief - Realiza la suma entre 2 números
 * \param float operadorA, es el primer número a sumar
 * \param float operadorB, es el segundo número a sumar
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \return (-1) Error / (0) Ok
 */

int sumar(float operadorA, float operadorB, float *pResultado) {

	int retorno = -1;

	*pResultado = operadorA + operadorB;
	retorno = 0;

	return retorno;
}

/*
* \brief - Realiza la resta entre 2 números
 * \param float operadorA, es el primer número a restar
 * \param float operadorB, es el segundo número a restar
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \return (-1) Error / (0) Ok
 */

int restar(float operadorA, float operadorB, float *pResultado) {

	int retorno = -1;

	*pResultado = operadorA - operadorB;
	retorno = 0;

	return retorno;
}

/*
* \brief - Realiza el producto entre 2 números
 * \param float operadorA, es el primer número a multiplicar
 * \param float operadorB, es el segundo número a multiplicar
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \return (-1) Error / (0) Ok
 */

int multiplicar(float operadorA, float operadorB, float *pResultado) {

	int retorno = -1;

	*pResultado = operadorA * operadorB;
	retorno = 0;

	return retorno;
}

/*
* \brief - Realiza el cociente entre 2 números
 * \param float operadorA, es el dividendo de la divisón
 * \param float operadorB, es el divisor de la divisón
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \return (-1) Error / (0) Ok
 */

int dividir(float operadorA, float operadorB, float *pResultado) {

	int retorno = -1;

	if (operadorB != 0) {
		*pResultado = operadorA / operadorB;
		retorno = 0;
	}

	return retorno;
}

/*
* \brief - Calcula el factorial de 2 numeros
 * \param float operadorA, primer numero a calcular
 * \param float operadorB, segundo numero a calcular
 * \param float* pResultadoUno, puntero al espacio de memoria donde se dejara el primer valor obtenido
 * \param float* pResultado, puntero al espacio de memoria donde se dejara el segundo valor obtenido
 * \return (-1) Error / (0) Ok
 */

int calcularFactorial(float operador,float *pResultado)
{
	int retorno = -1;

	//Calculo el factorial sólo para números naturales
	if (operador == (int)operador && operador>=0 )
	{
		*pResultado = operador;
		while(operador>1)
		{
			operador --;
			*pResultado *= operador;
		}
		retorno = 0;
	}
	return retorno;
}

/*
* \brief - Informa los resultados de las operaciones
 * \param int exitoOperacion[], el array que contiene el valor de éxito de las operaciones
 * \param float resultadoSuma, el resultado de la operacion Sumar
* \param float resultadoResta, el resultado de la operacion Restar
* \param float resultadoProdcuto, el resultado de la operacion Multiplicar
* \param float resultadoDivision, el resultado de la operacion Division
* \param float resultadoFactorialUno, el resultado de la operacion Factorial del primero operador
* \param float resultadoFactorialUno, el resultado de la operacion Factorial del segundo operador
 * \return (-1) Error / (0) Ok
 */

void informarResultados(int exitoOperacion[],float resultadoSuma,float resultadoResta, float resultadoProducto,float resultadoDivision,float resultadoFactorialUno, float resultadoFactorialDos)
{
	if(exitoOperacion[0] == 0)
	{
		printf("La suma entre los números ingresados es %.2f\n",resultadoSuma);
	}
	else
	{
		printf("No se realizar la suma\n");
	}
	if(exitoOperacion[1] == 0)
	{
		printf("La resta entre los números ingresados es %.2f\n",resultadoResta);
	}
	else
	{
		printf("No se realizar la resta\n");
	}
	if(exitoOperacion[2] == 0)
	{
		printf("El producto entre los números ingresados es %.2f\n",resultadoProducto);
	}
	else
	{
		printf("No se pudo realizar la multiplicación\n");
	}
	if(exitoOperacion[3] == 0)
	{
		printf("El cociente entre los números ingresados es %.2f\n",resultadoDivision);
	}
	else
	{
		printf("No se pudo realizar la división\n");
	}
	if(exitoOperacion[4] == 0)
	{
		printf("El factorial del primer operando es %.2f\n",resultadoFactorialUno);
	}
	else
	{
		printf("No se calcular el factorial de números decimales o negativos\n");
	}
	if(exitoOperacion[5] == 0)
	{
		printf("El factorial del segundo operando es %.2f\n",resultadoFactorialDos);
	}
	else
	{
		printf("No se calcular el factorial de números decimales o negativos\n");
	}
}


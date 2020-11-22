
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include "utn.h"
#define LIMITE_BUFFER_STRING 1000
static int myGets(char *cadena, int longitud);
static int isAlphNum(char cadena[]);


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

/**
 * \brief 	Verifica una cadena recibida como parametro para determinir
 * 			si es un nombre valido
 * \param char* cadena, Cadena a analizar
 * \param int limite, indica la cantidad de letras maxima de la cadena
 * \return (0) Indicar que no es un nombre valido / (1) Indica que que es un nombre valido
 *
 */
int esUnNombreValido(char* cadena,int limite)
{
	int respuesta = 1; // TODO OK

	for(int i=0; i<=limite && cadena[i] != '\0';i++)
	{
		//esta mal <----- A - Z -----> Esta mal
		if(	(cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			cadena[i] != '.')
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}


/**
 * \brief Solicita un nombre al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return (-1) Error / (0) Ok
 *
 */
int getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= limite &&
				esUnNombreValido(bufferString,limite) != 0 )
			{
				retorno = 0;
				//NO EXISTE pResultado = bufferString;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	}
	return retorno;

}

static int myGets(char *cadena, int longitud)
{
	__fpurge(stdin);
	fgets (cadena, longitud, stdin);
	cadena[strlen (cadena) - 1] = '\0';
	return 0;
}

/**
 * \brief Solicita un cuit al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int len, indica la cantidad de digitos que debe tener el cuit
 * \return (-1) Error / (0) Ok
 *
 */
int getCuit(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int len)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			len > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)== len)
			{
				retorno = 0;
				//NO EXISTE pResultado = bufferString;
				strncpy(pResultado,bufferString,len);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	}
	return retorno;
}

/*
* \brief Solicita numeros, letras y espacio al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param int limite, cantidad de espacio que puede almacenar la variable
 * return (-1) ERROR / 0 OK
 */
int utn_getAlphaNum(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pMensaje != NULL && pResultado != NULL && pMensajeError != NULL && reintentos >= 0 && limite > 0 )
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite) &&
				(isAlphNum(bufferString)==1))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}

/**
 * \brief Verifica si la cadena son numeros, letras con o sin tilde y espacio
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isAlphNum(char cadena[])
{
	int retorno = 1;
	int i;

	for(i=0 ; cadena[i] != '\0'; i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] != ' ') &&
			//(cadena[i] < 'á' || cadena[i] > 'ú') &&
			//(cadena[i] != 'é') &&
			(cadena[i] < '0' || cadena[i] > '9'))
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/*
* \brief Solicita un char al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param char minimo, valor minimo admitido
* \param char maximo, valor maximo admitido
 * return (-1) ERROR / 0 OK
 */
int utn_getChar(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pMensaje != NULL && pResultado != NULL && pMensajeError != NULL && reintentos >= 0 && limite > 0 )
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("Se quedo sin intentos");
		}
	}
	return retorno;
}

/**
 * \brief Ordena un array de enteros de manera DESCENDENTE
 * \param int pArray[] es el puntero al array a ser ordenado
 * \param int limite Es la longitud del array
 * \return la cantidad de iteraciones si OK o -1 para indicar error
 */
int utn_sortArrayInt(int pArray[], int limite)
{
	int flagSwap;
	int i;
	int contador = 0;
	int retorno = -1;
	int buffer;
	int nuevoLimite;

	if(pArray != NULL && limite >= 0)
	{
		do
		{
			nuevoLimite = limite -1;
			flagSwap = 0;
			for(i = 0; i < nuevoLimite; i++)
			{
				contador++;
				if(pArray[i] < pArray[i+1])
				{
					flagSwap = 1;
					buffer = pArray[i];
					pArray[i] = pArray[i + 1];
					pArray[i + 1] = buffer;
				}
			}
			nuevoLimite--;
			retorno = contador;
		}while(flagSwap);
	}
	return retorno;
}

int GetMayorValorArray(int *array, int len)
{
	int retorno = -1;
	int max;
	if(array != NULL && len > 0)
	{
		max = array[0];
		retorno = 0;
		for(int i=1; i < len; i++)
		{
			if(array[i] > max)
			{
				max = array[i];
				retorno = i;
			}
		}
	}
	return retorno;
}

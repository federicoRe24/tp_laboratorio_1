
#ifndef SRC_UTN_H_
#define SRC_UTN_H_

int getInt(char* mensaje, char* mensajeError, int* resultado, int reintentos, int maximo, int minimo);
int getFloat(char *mensaje,char *mensajeError,int reintentos,float *pResultado);
int sumar(float operadorA, float operadorB, float *pResultado);
int restar(float operadorA, float operadorB, float *pResultado);
int multiplicar(float operadorA, float operadorB, float *pResultado);
int dividir(float operadorA, float operadorB, float *pResultado);
int calcularFactorial(float operador,float *pResultado);
void informarResultados(int exitoOperacion[],float resultadoSuma,float resultadoResta, float resultadoProducto,float resultadoDivision,float resultadoFactorialUno, float resultadoFactorialDos);

#endif /* SRC_UTN_H_ */


#ifndef SRC_UTN_H_
#define SRC_UTN_H_

int getInt(char* mensaje, char* mensajeError, int* resultado, int reintentos, int maximo, int minimo);
int getFloat(char *mensaje,char *mensajeError,int reintentos,float *pResultado);
int esUnNombreValido(char* cadena,int limite);
int getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite);

#endif /* SRC_UTN_H_ */

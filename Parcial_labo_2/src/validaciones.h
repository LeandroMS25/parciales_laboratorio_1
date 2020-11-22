/*
 * validaciones.h
 * Author: Leandro Sobrino
 */

#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_

#define LEN_BUFFER_STRING 4096
int utn_getName(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len);
int utn_getCuit(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len);
int utn_getText(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len);
int utn_getNumberInt(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumberFloat(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int reintentos);
int isCuit(char* cadena,int len);
int isName(char* cadena,int len);
int isFloat(char* cadena, int len);
int isNumberInt(char* cadena, int len);

#endif /* VALIDACIONES_H_ */

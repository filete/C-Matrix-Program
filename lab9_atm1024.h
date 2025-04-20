/* Cabeceras del programa lab9_atm1024.c
 *  IMPORTANTE
 *  Este archivo debe ubicarse en el mismo directorio que lab9_atm1024.c    */
#pragma once
#define MATRIX_H 4
#define MATRIX_W 4

void leeMatriz_file(FILE *, float[MATRIX_W][MATRIX_H], int, int);
void leeMatriz_cmd(FILE *, float[MATRIX_W][MATRIX_H], int, int);
void mostrarMatriz(float [MATRIX_W][MATRIX_H],int ,int,char [2]);
void guardarMatriz(FILE *, float [MATRIX_W][MATRIX_H],int,int);
void sumM1_M2(float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],int,int);
void multM1_M2(float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],int,int);
void mostrarDeterminante(float [MATRIX_W][MATRIX_H]);
void mostrarMenu(FILE *, float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H]);
void tui(int);
void ejecutarOpcion(int, bool, FILE *, float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H]);
int salir();
int mostrarInfo();
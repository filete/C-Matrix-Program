/* Programa que lee matrices de documentos, las muestra por pantalla y hace cálculos
 * ver 11/abr/2025 by ATM */

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define CLEAR "clear"
#elif defined(_WIN32) || defined(_WIN64)
#define CLEAR "cls"
#endif

#include<stdio.h>
#include<stdlib.h>
#include "colorGuide.c"

#define I_FILENAME "./matriz.txt"
#define O_FILENAME "./resultado.txt"

#define ELM(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
#define MATRIX_H 4
#define MATRIX_W 4

void leeMatriz_file(FILE *, float[MATRIX_W][MATRIX_H], int, int);
void leeMatriz_cmd(FILE *, float[MATRIX_W][MATRIX_H], int, int);
void printMatriz(float [MATRIX_W][MATRIX_H],int ,int,char [2]);
void guardarMatriz(FILE*, float matriz[MATRIX_W][MATRIX_H],int,int);
void sumM1_M2(float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],int,int);

int main(void){
    float m1_4x4 [MATRIX_W][MATRIX_H];
    float m2_4x4 [MATRIX_W][MATRIX_H];
    float mr_4x4 [MATRIX_W][MATRIX_H];

    FILE *matriz_txt = fopen(I_FILENAME,"r");
    FILE *resultado_txt = fopen(O_FILENAME,"w+");

    system(CLEAR);
    leeMatriz_file(matriz_txt, m1_4x4, MATRIX_W, MATRIX_H);

        leeMatriz_cmd(resultado_txt, m2_4x4, MATRIX_W, MATRIX_H);
        fclose(resultado_txt);
        printf(R_GREEN"Archivo creado correctamente :)\n"R_RESET);
    }else{
        printf(R_RED"Error al crear el archivo :(\n"R_RESET);
    }
        //system("clear");
        system(CLEAR);
        //printf("\e[1;1H\e[2J");
    sumM1_M2(m1_4x4, m2_4x4, mr_4x4, MATRIX_W, MATRIX_H);
    printMatriz(mr_4x4, MATRIX_H,MATRIX_W,"MR");
    guardarMatriz(resultado_txt,mr_4x4,MATRIX_W,MATRIX_H);
    return 0;
}



void leeMatriz_file(FILE *matriz_txt, float matriz[MATRIX_W][MATRIX_H], int w, int h){
    int x,y;

    if(matriz_txt!= NULL){
        //printf("\nMatriz "R_CYAN"M1"R_RESET" del documento "U_YELLOW"%s"R_RESET":\n", I_FILENAME + 2);
        for(size_t i = 0; i < (w*h); i++){
        y = i % w;
        x = (int) i/h;

            fscanf(matriz_txt,"%f",&matriz[x][y]);
/*        i % w == 0 ? printf("\t%g ",matriz[x][y]) :       DEBUGGING
            (i % w < 3 ? (printf("%g ",matriz[x][y]) ) :
                (printf("%g \n",matriz[x][y]) )
            );*/

        }
    fclose(matriz_txt);
        printf(R_GREEN"Archivo " U_YELLOW "%s"R_RESET R_GREEN" leido correctamente :)\n"R_RESET, I_FILENAME +2);
    }else{
    char cierrePorError;
        printf(R_RED"Error al abrir el archivo " U_YELLOW "%s" R_RESET R_RED" :(\n"R_RESET,I_FILENAME +2);
        printf("\nSe va a cerrar el programa. [Introduzca "U_RED"cualquier tecla"R_RESET" para salir]\n");
        scanf(" %c",&cierrePorError);
        if(cierrePorError){
            exit(1);
        }
    }
}

void leeMatriz_cmd(FILE *resultado_txt, float matriz[MATRIX_W][MATRIX_H], int w, int h){
    int x, y;

    if(resultado_txt != NULL){

    printf("\nIntroduzca la matriz "R_CYAN"M2"R_RESET" para almacenarla en el documento "U_YELLOW"%s"R_RESET":\n", O_FILENAME + 2);

    for(size_t i = 0; i < (w*h) ; i++){
        y = i % w;
        x = (int) i/h;

        printf("Introduce el valor para la posición "R_BLUE"%u,%u"R_RESET": ",x + 1,y + 1);
        scanf("%f", &matriz[x][y]);

        i % w == 0 ? fprintf(resultado_txt ,"%8g",matriz[x][y]) :
            (i % w < 3 ? (fprintf(resultado_txt,"%8g",matriz[x][y]) ) :
                (fprintf(resultado_txt,"%8g \n",matriz[x][y]) ));
    }
}

void printMatriz(float matriz[MATRIX_W][MATRIX_H],int w, int h, char nombre[2]){
    int x,y;
    printf("\nMatriz "R_CYAN"%s"R_RESET":\n", nombre);

    for(size_t i = 0; i < (w*h); i++){
        y = i % w;
        x = (int) i/h;

        i % w == 0 ? printf("%8g ",matriz[x][y]) :
            (i % w < 3 ? (printf("%8g ",matriz[x][y]) ) :
                (printf("%8g \n",matriz[x][y]) )
            );}
}

void guardarMatriz(FILE* file, float matriz[MATRIX_W][MATRIX_H], int w, int h){
    int x,y;

    if(file != NULL){
        for(size_t i = 0; i < (w*h); i++){
            y = i % w;
            x = (int) i/h;

           scanf("%f", &matriz[x][y]);

            i % w == 0 ? fprintf(file ,"%8g",matriz[x][y]) :
                (i % w < 3 ? (fprintf(file,"%8g",matriz[x][y]) ) :
                    (fprintf(file,"%8g \n",matriz[x][y]) ));
        }
        fclose(file);
        printf(R_GREEN"Archivo creado correctamente :)\n"R_RESET);
    }else{
        printf(R_RED"Error al crear el archivo :(\n"R_RESET);
    }
}

void sumM1_M2(
    float m1[MATRIX_W][MATRIX_H],
    float m2[MATRIX_W][MATRIX_H],
    float mr[MATRIX_W][MATRIX_H],
    int w, int h
){
    int x,y;

    for(size_t i = 0; i < (w*h); i++){
        y = i % w;
        x = (int) i/h;

        mr[x][y] = m1[x][y] + m2[x][y];
    }
}
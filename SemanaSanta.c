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
void mostrarMatriz(float [MATRIX_W][MATRIX_H],int ,int,char [2]);
void guardarMatriz(FILE *, float [MATRIX_W][MATRIX_H],int,int);
void sumM1_M2(float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],int,int);
void multM1_M2(float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],float [MATRIX_W][MATRIX_H],int,int);
void mostrarMenu();
void ui(int);
void ejecutarOpcion(int, FILE *, float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H]);
void salir();

int main(void){
    float m1_4x4 [MATRIX_W][MATRIX_H];
    float m2_4x4 [MATRIX_W][MATRIX_H];
    float mr_4x4 [MATRIX_W][MATRIX_H];

    FILE *matriz_txt = fopen(I_FILENAME,"r");
    FILE *resultado_txt = fopen(O_FILENAME,"w+");

    system(CLEAR);

    leeMatriz_file(matriz_txt, m1_4x4, MATRIX_W, MATRIX_H);
    leeMatriz_cmd(resultado_txt, m2_4x4, MATRIX_W, MATRIX_H);
    multM1_M2(m1_4x4,m2_4x4,mr_4x4, MATRIX_W, MATRIX_H);
    //mostrarMenu(resultado_txt, m1_4x4, m2_4x4, mr_4x4);
    //sumM1_M2(m1_4x4, m2_4x4, mr_4x4, MATRIX_W, MATRIX_H);
    mostrarMatriz(mr_4x4, MATRIX_H,MATRIX_W,"MR");
    //guardarMatriz(resultado_txt,mr_4x4,MATRIX_W,MATRIX_H);
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
        printf(R_RED"ERROR al abrir el archivo " U_YELLOW "%s" R_RESET R_RED" :(\n"R_RESET,I_FILENAME +2);
        printf("\nSe va a cerrar el programa. [Introduzca "U_RED"cualquier tecla"R_RESET" para salir]\n");
        scanf(" %c",&cierrePorError);
        if(cierrePorError){
            exit(1);
        }
    }
}

void leeMatriz_cmd(FILE *file, float matriz[MATRIX_W][MATRIX_H], int w, int h){
    int x, y;
    char c;

    if(file != NULL){
        printf("\nIntroduzca la matriz "R_CYAN"M2"R_RESET" para almacenarla en el documento "U_YELLOW"%s"R_RESET":\n", O_FILENAME + 2);
        fclose(file);
        for(size_t i = 0; i < (w*h) ; i++){
            y = i % w;
            x = (int) i/h;

            printf("Introduce el valor para la posición "R_BLUE"%u,%u"R_RESET": ",x + 1,y + 1);
            scanf("%f", &matriz[x][y]);

            i % w == 0 ? fprintf(file ,"%8g",matriz[x][y]) :
                (i % w < 3 ? (fprintf(file,"%8g",matriz[x][y]) ) :
                    (fprintf(file,"%8g \n",matriz[x][y]) ));
        }
    }else{
        char cierrePorError;
        printf(R_RED"ERROR al abrir el archivo " U_YELLOW "%s" R_RESET R_RED" :(\n"R_RESET,I_FILENAME +2);
        printf(R_RED"Compruebe, en caso de ya existir, si el fichero resultado.txt tiene permisos de escritura"R_RESET);
        printf("\nSe va a cerrar el programa. [Introduzca "U_RED"cualquier tecla"R_RESET" para salir]\n");
        scanf(" %c",&cierrePorError);
        if(cierrePorError){
            exit(1);
        }
    }

    printf("\n"R_GREEN"Archivo creado correctamente :)\n"R_RESET);
    printf("Para continuar introduzca cualquier tecla: ");
    scanf(" %c", &c);
    if(c){
        system(CLEAR);
        //printf("\e[1;1H\e[2J");
        //printf("c es %d",c);      DEBUGGING
    }
}

void mostrarMatriz(float matriz[MATRIX_W][MATRIX_H],int w, int h, char nombre[2]){
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

void guardarMatriz(FILE *file, float matriz[MATRIX_W][MATRIX_H], int w, int h){
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

void multM1_M2(
    float m1[MATRIX_W][MATRIX_H],
    float m2[MATRIX_W][MATRIX_H],
    float mr[MATRIX_W][MATRIX_H],
    int w, int h
){
    int x,y;

    for(size_t i = 0; i < (w*h); i++){
        y = i % w;
        x = (int) i/h;

        mr[x][y] =
        m1[x][0] * m2[0][y] +
        m1[x][1] * m2[1][y] +
        m1[x][2] * m2[2][y] +
        m1[x][3] * m2[3][y];
    }
}

void mostrarMenu(FILE file,
    float m1[MATRIX_W][MATRIX_H],
    float m2[MATRIX_W][MATRIX_H],
    float mr[MATRIX_W][MATRIX_H]){

    int selector = 1;
    char tecla;
    while(1){
        scanf(" %[0-9jk]",&tecla);
        if(tecla == 'k'){
            selector == 1 ? selector = 8 : (selector -= 1);
        }else{
            if(tecla == 'j'){
                selector == 8 ? selector = 1 : (selector += 1);
            }
        }
        ui(selector);
    }
}

void ui(int selector){
    system(CLEAR);
    switch(selector) {
        case 2:
            printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER] o pulse el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
            B_GREEN"> [ 2 ] Mostrar matriz M2\n"R_RESET
            "  [ 3 ] Calcular MR = M1 + M2\n"
            "  [ 4 ] Calcular MR = M1 * M2\n"
            "  [ 5 ] Mostrar matriz MR\n"
            "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
            "  [ 7 ] Mostrar matriz M1\n"
            "  [ 8 ] Mostrar matriz M1\n\n");
            break;
        case 3:
            printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER] o pulse el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
            "  [ 2 ] Mostrar matriz M2\n"
            B_GREEN"> [ 3 ] Calcular MR = M1 + M2\n"R_RESET
            "  [ 4 ] Calcular MR = M1 * M2\n"
            "  [ 5 ] Mostrar matriz MR\n"
            "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
            "  [ 7 ] Mostrar matriz M1\n"
            "  [ 8 ] Mostrar matriz M1\n");
            break;
        case 4:
            printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER] o pulse el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
            "  [ 2 ] Mostrar matriz M2\n"
            "  [ 3 ] Calcular MR = M1 + M2\n"
            B_GREEN"> [ 4 ] Calcular MR = M1 * M2\n"R_RESET
            "  [ 5 ] Mostrar matriz MR\n"
            "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
            "  [ 7 ] Mostrar matriz M1\n"
            "  [ 8 ] Mostrar matriz M1\n");
            break;
        case 5:
            printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER] o pulse el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
            "  [ 2 ] Mostrar matriz M2\n"
            "  [ 3 ] Calcular MR = M1 + M2\n"
            "  [ 4 ] Calcular MR = M1 * M2\n"
            B_GREEN"> [ 5 ] Mostrar matriz MR\n"R_RESET
            "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
            "  [ 7 ] Mostrar matriz M1\n"
            "  [ 8 ] Mostrar matriz M1\n");
            break;
        case 6:
            printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER] o pulse el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
            "  [ 2 ] Mostrar matriz M2\n"
            "  [ 3 ] Calcular MR = M1 + M2\n"
            "  [ 4 ] Calcular MR = M1 * M2\n"
            "  [ 5 ] Mostrar matriz MR\n"
            B_GREEN"> [ 6 ] Guardar MR (en \"resultado.txt\")\n"R_RESET
            "  [ 7 ] Mostrar matriz M1\n"
            "  [ 8 ] Mostrar matriz M1\n");
            break;
        case 7:
            printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER] o pulse el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
            "  [ 2 ] Mostrar matriz M2\n"
            "  [ 3 ] Calcular MR = M1 + M2\n"
            "  [ 4 ] Calcular MR = M1 * M2\n"
            "  [ 5 ] Mostrar matriz MR\n"
            "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
            B_GREEN"> [ 7 ] Mostrar matriz M1\n"R_RESET
            "  [ 8 ] Mostrar matriz M1\n");
            break;
        case 8:
            printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER] o pulse el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
            "  [ 2 ] Mostrar matriz M2\n"
            "  [ 3 ] Calcular MR = M1 + M2\n"
            "  [ 4 ] Calcular MR = M1 * M2\n"
            "  [ 5 ] Mostrar matriz MR\n"
            "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
            "  [ 7 ] Mostrar matriz M1\n"
            B_GREEN"> [ 8 ] Mostrar matriz M1\n"R_RESET);
            break;
        default:
            printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER] o pulse el no. de opción:\n\n"
            B_GREEN"> [ 1 ] Mostrar matriz M1\n"R_RESET
            "  [ 2 ] Mostrar matriz M2\n"
            "  [ 3 ] Calcular MR = M1 + M2\n"
            "  [ 4 ] Calcular MR = M1 * M2\n"
            "  [ 5 ] Mostrar matriz MR\n"
            "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
            "  [ 7 ] Mostrar matriz M1\n"
            "  [ 8 ] Mostrar matriz M1\n");
            break;
    }
    //system(CLEAR);
}

void ejecutarOpcion(int selector,FILE *file,
    float m1[MATRIX_W][MATRIX_H],
    float m2[MATRIX_W][MATRIX_H],
    float mr[MATRIX_W][MATRIX_H]){

    switch(selector){
        case 2:
        case '2':
            mostrarMatriz(m2, MATRIX_W, MATRIX_H, "M2");
            break;
        case 3:
        case '3':
            sumM1_M2(m1, m2, mr, MATRIX_W, MATRIX_H);
            break;
        case 4:
        case '4':

            break;
        case 5:
        case '5':
            mostrarMatriz(mr, MATRIX_W, MATRIX_H, "MR");
            break;
        case 6:
        case '6':
            guardarMatriz(file, mr, MATRIX_W, MATRIX_H);
            break;
        case 7:
        case '7':

            break;
        case 8:
        case '8':
            salir();
            break;
        case '1':
        default:
            mostrarMatriz(m1, MATRIX_W, MATRIX_H, "M1");
            break;
    }
}

void salir(){
    char salida;
    system(CLEAR);
    printf(B_BLACK"DESEA SALIR?\n"R_RESET
    BU_GREEN"S"R_RESET B_GREEN"i"R_RESET" (Introduzca \"S\")\n"
    BU_RED  "N"R_RESET B_RED  "o"R_RESET" (Introduzca \"N\")\n");
    scanf(" %[sInN]",&salida);
    if(salida == 's' || salida == 'S'){
        exit(1);
    }
}
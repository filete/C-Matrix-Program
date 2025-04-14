/* Programa que lee matrices de documentos, las muestra por pantalla y hace cálculos
 * ver 11/abr/2025 by ATM */

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define CLEAR "clear"
#elif defined(_WIN32) || defined(_WIN64)
#define CLEAR "cls"
#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "colorGuide.h"

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
void mostrarDeterminante(float [MATRIX_W][MATRIX_H]);
void mostrarMenu(FILE *, float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H]);
void tui(int);
void ejecutarOpcion(int, bool, FILE *, float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H], float [MATRIX_W][MATRIX_H]);
int salir();
void mostrarInfo();

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
    mostrarMenu(resultado_txt, m1_4x4, m2_4x4, mr_4x4);
  
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
        printf(R_GREEN"\nArchivo " U_YELLOW "%s"R_RESET R_GREEN" leido correctamente "R_YELLOW":)\n"R_RESET, I_FILENAME +2);
    }else{
    char cierrePorError;
        printf(R_RED"\n\nERROR al abrir el archivo " U_YELLOW "%s" R_RESET R_RED" :(\n"R_RESET,I_FILENAME +2);
        printf("\nCompruebe que el fichero "U_BLACK"%s"R_RESET" se encuentra en el directorio donde se encuentra el programa.\n", I_FILENAME+2);
        printf("\nSe va a cerrar el programa. [Introduzca "U_RED"cualquier tecla"R_RESET" para salir]\n");
        scanf(" %c",&cierrePorError);
        if(cierrePorError){
            exit(1);
        }
    }
}

void leeMatriz_cmd(FILE *resultado_txt, float matriz[MATRIX_W][MATRIX_H], int w, int h){
    int x, y;
    char c;

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
        fclose(resultado_txt);
    }else{
        char cierrePorError;
        printf(R_RED"\nERROR al abrir el archivo " U_YELLOW "%s" R_RESET R_RED" :(\n"R_RESET,O_FILENAME +2);
        printf(R_RED"\nCompruebe, en caso de ya existir, si el fichero resultado.txt tiene permisos de escritura"R_RESET);
        printf("\nSe va a cerrar el programa. [Introduzca "U_RED"cualquier tecla"R_RESET" para salir]\n");
        scanf(" %c",&cierrePorError);
        if(cierrePorError){
            exit(1);
        }
    }

    printf("\n"R_GREEN"Archivo "U_YELLOW"%s"R_RESET R_GREEN" creado correctamente "R_YELLOW":)\n"R_RESET,O_FILENAME+2);
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
    printf("\n\nMatriz "R_CYAN"%s"R_RESET":\n\n", nombre);

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
    file = fopen(O_FILENAME,"w+");
    if(file != NULL){
        for(size_t i = 0; i < (w*h); i++){
            y = i % w;
            x = (int) i/h;

            i % w == 0 ? fprintf(file ,"%8g",matriz[x][y]) :
                (i % w < 3 ? (fprintf(file,"%8g",matriz[x][y]) ) :
                    (fprintf(file,"%8g \n",matriz[x][y]) ));
        }
        fclose(file);
        printf(R_GREEN"\n\nArchivo "U_YELLOW"%s"R_RESET R_GREEN" creado correctamente "R_YELLOW":)\n"R_RESET,O_FILENAME+2);
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
    printf(R_GREEN"\n\nSuma realizada correctamente "R_YELLOW":)"R_RESET);
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
    printf(R_GREEN"\n\nProducto realizado correctamente "R_YELLOW":)"R_RESET);
}

void mostrarDeterminante(float matriz[MATRIX_W][MATRIX_H]){
    float determinante = 0;
    for(size_t i = 0; i < MATRIX_W ; i++){
        determinante += (matriz[0][i] * matriz[1][(i+1) % 4] * matriz[2][(i+2) % 4] * matriz[3][(i+3) %4] -
        matriz[0][i] * matriz[1][(i-1) % 4] * matriz[2][(i-2) % 4] * matriz[3][(i-3) %4]);
    }
    printf("\nDeterminante: %g\n", determinante);
}

void mostrarMenu(FILE * file,
    float m1[MATRIX_W][MATRIX_H],
    float m2[MATRIX_W][MATRIX_H],
    float mr[MATRIX_W][MATRIX_H]){

    int selector = 1;
    bool seleccion;
    char tecla;
    while(1){
        seleccion = false;
        tecla = 0;

        scanf("%c",&tecla);

        if(tecla == 'k'){
            selector == 1 ? selector = 8 : (selector -= 1);
        }else{
            if(tecla == 'j'){
                selector == 8 ? selector = 1 : (selector += 1);
            }else{
                if(tecla >= '0' && tecla <= '9'){
                    selector = tecla;
                    seleccion = true;
                }else{
                    if(tecla == 'c' || tecla == 'C'){
                        seleccion = true;}
                }
            }
        }
        tui(selector);
        if(seleccion){ejecutarOpcion(selector, seleccion, file, m1, m2, mr);}
    }
}

void tui(int selector){
    system(CLEAR);
    switch(selector) {
    case 2:
        printf(BU_BLACK"\n\nSeleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER], confirme con "U_BLACK"C"R_RESET"\nO pulse el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
        B_GREEN"> [ 2 ] Mostrar matriz M2\n"R_RESET
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
        "  [ 7 ] Guardar MR y mostrar determinante\n"
        "  [ 8 ] Salir\n\n");
        break;
    case 3:
        printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER], confirme con "U_BLACK"C"R_RESET"\nO pulse el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        B_GREEN"> [ 3 ] Calcular MR = M1 + M2\n"R_RESET
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
        "  [ 7 ] Guardar MR y mostrar determinante\n"
        "  [ 8 ] Salir\n");
        break;
    case 4:
        printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER], confirme con "U_BLACK"C"R_RESET"\nO pulse el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        B_GREEN"> [ 4 ] Calcular MR = M1 * M2\n"R_RESET
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
        "  [ 7 ] Guardar MR y mostrar determinante\n"
        "  [ 8 ] Salir\n");
        break;
    case 5:
        printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER], confirme con "U_BLACK"C"R_RESET"\nO pulse el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        B_GREEN"> [ 5 ] Mostrar matriz MR\n"R_RESET
        "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
        "  [ 7 ] Guardar MR y mostrar determinante\n"
        "  [ 8 ] Salir\n");
        break;
    case 6:
        printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER], confirme con "U_BLACK"C"R_RESET"\nO pulse el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        B_GREEN"> [ 6 ] Guardar MR (en \"resultado.txt\")\n"R_RESET
        "  [ 7 ] Guardar MR y mostrar determinante\n"
        "  [ 8 ] Salir\n");
            break;
    case 7:
        printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER], confirme con "U_BLACK"C"R_RESET"\nO pulse el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
        B_GREEN"> [ 7 ] Guardar MR y mostrar determinante\n"R_RESET
        "  [ 8 ] Salir\n");
        break;
    case 8:
        printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER], confirme con "U_BLACK"C"R_RESET"\nO pulse el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
        "  [ 7 ] Guardar MR y mostrar determinante\n"
        B_GREEN"> [ 8 ] Salir\n"R_RESET);
        break;
    default:
        printf(BU_BLACK"Seleccione una opción."R_RESET"\nNavegue con ["U_BLACK"j(↓)"R_RESET", "U_BLACK"k(↑)"R_RESET" + ENTER], confirme con "U_BLACK"C"R_RESET"\nO pulse el no. de opción:\n\n"
        B_GREEN"> [ 1 ] Mostrar matriz M1\n"R_RESET
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
        "  [ 7 ] Guardar MR y mostrar determinante\n"
        "  [ 8 ] Salir\n");
        break;
    }
}

void ejecutarOpcion(int selector, bool seleccion,
    FILE * file,
    float m1[MATRIX_W][MATRIX_H],
    float m2[MATRIX_W][MATRIX_H],
    float mr[MATRIX_W][MATRIX_H]){

    char volver;
    volver = 0;
    system(CLEAR);

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
            multM1_M2(m1, m2, mr, MATRIX_W, MATRIX_H);
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
            guardarMatriz(file, mr, MATRIX_W, MATRIX_H);
            mostrarDeterminante(mr);
            break;
        case 8:
        case '8':
            if(salir()){
                volver = 'v';
            }
            break;
        case '1':
        default:
                mostrarMatriz(m1, MATRIX_W, MATRIX_H, "M1");
                break;
        }
    printf("\nPulse "U_BLACK"V"R_RESET" volver al menú.\n\n");
    while(volver != 'v' && volver != 'V'){
        scanf("%c", &volver);
    }
}

int salir(){
    char salida;
    system(CLEAR);
    printf(B_BLACK"\n\nDESEA SALIR?\n\n"R_RESET
    BU_RED  "S"R_RESET B_RED  "i"R_RESET" \t(Introduzca \"S\")\n"
    BU_GREEN"N"R_RESET B_GREEN"o"R_RESET" \t(Introduzca \"N\")\n"
    U_BLACK"I"R_RESET R_BLACK"nfo"R_RESET" \t(Introduzca \"I\")\n");
    scanf(" %[sInNiI]",&salida);
    if(salida == 's' || salida == 'S'){
        exit(1);
    }else{
        if(salida == 'i' || salida == 'I'){
            mostrarInfo();
        }
    }
    return 1;
}

void mostrarInfo(){
    system(CLEAR);
    printf("\nPrograma realizado por Albert Tambwe Miñón Apr/2025"
    "\nPara Progrmación - Ingeniería Informática - UBU\n\n"
    U_BLUE"https://github.com/filete/C-Matrix-Program-For-Semana-Santa.git\n"R_RESET);
}
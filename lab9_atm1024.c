/* lab9_atm1024
 * Programa que lee y escribe matrices desde y en ficheros,
 *  a través de un menú interactivo permite mostrar y almacenar matrices,
 *  y realizar cálculos matriciales.

 * Compilador usado: gcc
 * SO probados: MS Windows, Linux (Arch y Ubuntu)
 * Dependencias: lab9_atm1024.h y colorGuide.h

 * Realizado para la asignatura Programación
 *  Grado en Ingeniería Informática - Universidad de Burgos
 * Autor: Albert Tambwe Miñón
 * Fecha: 14/15 abr 2025
 * ver 1.0.1
 *      1.0.0 Programa final
 *      1.0.1 Implementación de comentarios en el código
 * */

// Definición del CLEAR para una mayor claridad al momento de usar el programa
// en función del SO donde se compile se realizará una deefinición u otra
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define CLEAR "clear"
#elif defined(_WIN32) || defined(_WIN64)
#define CLEAR "cls"
#endif

// Cabeceras de las librerías y ficheros para el correcto funcionar del programa
// IMPORTANTE -> Mantener los ficheros "lab9_atm1024.c" y "colorGuide.h" en la carpeta donde se ubique el programa
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lab9_atm1024.h"               // Cabeceras de las funciones declaradas en el programa
#include "colorGuide.h"                 // Archivo de definición de colores de la consola

#define I_FILENAME "./matriz.txt"       // Fichero con matriz de entrada
#define O_FILENAME "./resultado.txt"    // Fichero con matriz de salida

#define MATRIX_H 4                      // Alto de la matriz, en caso de tener que cambiarse en un futuro
#define MATRIX_W 4                      // Ancho de la matriz, en caso de tener que cambiarse en un futuro

int main(void){
    // Declaración de los arrays 2D de las matrices a utilizar
    float m1_4x4 [MATRIX_W][MATRIX_H];
    float m2_4x4 [MATRIX_W][MATRIX_H];
    float mr_4x4 [MATRIX_W][MATRIX_H];

    // Declaración de los ficheros a utilizar
    FILE *matriz_txt = fopen(I_FILENAME,"r");
    FILE *resultado_txt = fopen(O_FILENAME,"w+");

    system(CLEAR);

    // Llamada a las funciones del programa
    leeMatriz_file(matriz_txt, m1_4x4, MATRIX_W, MATRIX_H);
    leeMatriz_cmd(resultado_txt, m2_4x4, MATRIX_W, MATRIX_H);
    multM1_M2(m1_4x4,m2_4x4,mr_4x4, MATRIX_W, MATRIX_H);
    mostrarMenu(resultado_txt, m1_4x4, m2_4x4, mr_4x4);

    return 0;
}

/*  Función que lee una matriz del fichero de entrada y la almacena en un Arr.2D .  No he considerado necesaria la lectura adelantada.
 *  @Param_1    I/ fichero de entrada
 *  @Param_2    I/ array matriz
 *  @Param_3,4  I/ alto y ancho de la matriz  */
void leeMatriz_file(FILE *matriz_txt, float matriz[MATRIX_W][MATRIX_H], int w, int h){
    int x,y;

    if(matriz_txt!= NULL){
        for(size_t i = 0; i < (w*h); i++){
        y = i % w;
        x = (int) i/h;
            fscanf(matriz_txt,"%f",&matriz[x][y]);
        }
        fclose(matriz_txt);
        printf(R_GREEN"\nArchivo " U_YELLOW "%s"R_RESET R_GREEN" leido correctamente "R_YELLOW":)\n"R_RESET, I_FILENAME +2);
    }else{
    char cierrePorError;
        printf(R_RED"\n\nERROR al abrir el archivo " U_YELLOW "%s" R_RESET R_RED" :(\n"R_RESET,I_FILENAME +2);
        printf("\nCompruebe que el fichero "UNDERL"%s"R_RESET" se encuentra en el directorio donde se encuentra el programa.\n", I_FILENAME+2);
        printf("\nSe va a cerrar el programa. [Introduzca "U_RED"cualquier tecla"R_RESET" para salir]\n");
        scanf(" %c",&cierrePorError);
        if(cierrePorError){
            exit(1);
        }
    }
}

/*  Función que lee una matriz desde la terminal y la almacena en un Arr.2D .
 *  @Param_1    I/ fichero de salida
 *  @Param_2    I/ array matriz
 *  @Param_3,4  I/ ancho y alto de la matriz  */
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
    }
}

/*  Función que muestra una matriz en la terminal
 *  @Param_1    I/ array matriz
 *  @Param_2,3  I/ ancho y alto de la matriz
 *  @Param_4    I/ nombre de la matriz (2 dígitos máx.)     */
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

/*  Función que almacena una matriz en un archivo de salida
 *  @Param_1    I/ fichero de salida
 *  @Param_2    I/ array matriz_t
 *  @Param_3,4  I/ ancho y alto de la matriz        */
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

/*  Función que suma 2 matrices y almacena el resultado en otra matriz M1+M2 = MR
 *  @Param_1    I/ matriz M1
 *  @Param_2    I/ matriz M2
 *  @Param_3    I/ matriz MR
 *  @Param_4,5  I/ ancho y alto de las matrices     */
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

/*  Función que multiplica 2 matrices y almacena el resultado en otra matriz M1*M2 = MR
 *  @Param_1    I/ matriz M1
 *  @Param_2    I/ matriz M2
 *  @Param_3    I/ matriz MR
 *  @Param_4,5  I/ ancho y alto de las matrices     */
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

/*  Función que calcula el determinante de una matriz
 *  @Param_1    I/ array matriz     */
void mostrarDeterminante(float matriz[MATRIX_W][MATRIX_H]){
    float determinante = 0;
    for(size_t i = 0; i < MATRIX_W ; i++){
        determinante += (matriz[0][i] * matriz[1][(i+1) % 4] * matriz[2][(i+2) % 4] * matriz[3][(i+3) %4] -
        matriz[0][i] * matriz[1][(i-1) % 4] * matriz[2][(i-2) % 4] * matriz[3][(i-3) %4]);
    }
    printf("\n"BOLDUND"Determinante"R_RESET": %g\n", determinante);
}

/*  Función que procesa las entradas del el menú por la terminal
 *  @Param_1    I/ fichero de salida para las funciones que requieran almacenar un resultado
 *  @Param_2    I/ matriz M1
 *  @Param_3    I/ matriz M2
 *  @Param_4    I/ matriz MR        */
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

/*  Función que muestra el menú por la terminal
 *  @Param_1    I/ índice de la opción actual       */
void tui(int selector){
    system(CLEAR);
    switch(selector) {
    case 2:
        printf(BOLDUND"\nSeleccione una opción."R_RESET"\nNavegue con ["UNDERL"j(↓)"R_RESET", "UNDERL"k(↑)"R_RESET" + ENTER], confirme con "UNDERL"C"R_RESET"\nO introduzca el no. de opción:\n\n"
            "  [ 1 ] Mostrar matriz M1\n"
        B_GREEN"> [ 2 ] Mostrar matriz M2\n"R_RESET
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Guardar MR (en \"resultado.txt\")\n"
        "  [ 7 ] Calcular y mostrar determinante\n"
        "  [ 8 ] Salir\n\n");
        break;
    case 3:
        printf(BOLDUND"\nSeleccione una opción."R_RESET"\nNavegue con ["UNDERL"j(↓)"R_RESET", "UNDERL"k(↑)"R_RESET" + ENTER], confirme con "UNDERL"C"R_RESET"\nO introduzca el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        B_GREEN"> [ 3 ] Calcular MR = M1 + M2\n"R_RESET
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Calcular (en \"resultado.txt\")\n"
        "  [ 7 ] Calcular y mostrar determinante\n"
        "  [ 8 ] Salir\n");
        break;
    case 4:
        printf(BOLDUND"\nSeleccione una opción."R_RESET"\nNavegue con ["UNDERL"j(↓)"R_RESET", "UNDERL"k(↑)"R_RESET" + ENTER], confirme con "UNDERL"C"R_RESET"\nO introduzca el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        B_GREEN"> [ 4 ] Calcular MR = M1 * M2\n"R_RESET
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Calcular (en \"resultado.txt\")\n"
        "  [ 7 ] Calcular y mostrar determinante\n"
        "  [ 8 ] Salir\n");
        break;
    case 5:
        printf(BOLDUND"\nSeleccione una opción."R_RESET"\nNavegue con ["UNDERL"j(↓)"R_RESET", "UNDERL"k(↑)"R_RESET" + ENTER], confirme con "UNDERL"C"R_RESET"\nO introduzca el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        B_GREEN"> [ 5 ] Mostrar matriz MR\n"R_RESET
        "  [ 6 ] Calcular (en \"resultado.txt\")\n"
        "  [ 7 ] Calcular y mostrar determinante\n"
        "  [ 8 ] Salir\n");
        break;
    case 6:
        printf(BOLDUND"\nSeleccione una opción."R_RESET"\nNavegue con ["UNDERL"j(↓)"R_RESET", "UNDERL"k(↑)"R_RESET" + ENTER], confirme con "UNDERL"C"R_RESET"\nO introduzca el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        B_GREEN"> [ 6 ] Calcular (en \"resultado.txt\")\n"R_RESET
        "  [ 7 ] Calcular y mostrar determinante\n"
        "  [ 8 ] Salir\n");
            break;
    case 7:
        printf(BOLDUND"\nSeleccione una opción."R_RESET"\nNavegue con ["UNDERL"j(↓)"R_RESET", "UNDERL"k(↑)"R_RESET" + ENTER], confirme con "UNDERL"C"R_RESET"\nO introduzca el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Calcular (en \"resultado.txt\")\n"
        B_GREEN"> [ 7 ] Calcular y mostrar determinante\n"R_RESET
        "  [ 8 ] Salir\n");
        break;
    case 8:
        printf(BOLDUND"\nSeleccione una opción."R_RESET"\nNavegue con ["UNDERL"j(↓)"R_RESET", "UNDERL"k(↑)"R_RESET" + ENTER], confirme con "UNDERL"C"R_RESET"\nO introduzca el no. de opción:\n\n"
        "  [ 1 ] Mostrar matriz M1\n"
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Calcular (en \"resultado.txt\")\n"
        "  [ 7 ] Calcular y mostrar determinante\n"
        B_GREEN"> [ 8 ] Salir\n"R_RESET);
        break;
    default:
        printf(BOLDUND"\nSeleccione una opción."R_RESET"\nNavegue con ["UNDERL"j(↓)"R_RESET", "UNDERL"k(↑)"R_RESET" + ENTER], confirme con "UNDERL"C"R_RESET"\nO introduzca el no. de opción:\n\n"
        B_GREEN"> [ 1 ] Mostrar matriz M1\n"R_RESET
        "  [ 2 ] Mostrar matriz M2\n"
        "  [ 3 ] Calcular MR = M1 + M2\n"
        "  [ 4 ] Calcular MR = M1 * M2\n"
        "  [ 5 ] Mostrar matriz MR\n"
        "  [ 6 ] Calcular (en \"resultado.txt\")\n"
        "  [ 7 ] Calcular y mostrar determinante\n"
        "  [ 8 ] Salir\n");
        break;
    }
}

/*  Función que ejecuta las opciones seleccionadas del menú
 *  @Param_1    I/ índice la opción actual
 *  @Param_2    I/ estado de la selección (Seleccionada/No seleccionada)
 *  @Param_3    I/ matriz M1
 *  @Param_4    I/ matriz M2
 *  @Param_5    I/ matriz MR        */
void ejecutarOpcion(int selector, bool seleccion,
    FILE * file,
    float m1[MATRIX_W][MATRIX_H],
    float m2[MATRIX_W][MATRIX_H],
    float mr[MATRIX_W][MATRIX_H]){

    char volver = 0;
    bool yaVolvio = false;
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
            mostrarDeterminante(mr);
            break;
        case 8:
        case '8':
            if(salir()){
               yaVolvio = true;
            }
            break;
        case '1':
        default:
                mostrarMatriz(m1, MATRIX_W, MATRIX_H, "M1");
                break;
        }
    if(!yaVolvio){
        printf("\nIntroduzca "UNDERL"V"R_RESET" para volver al menú.\n\n");
        while(volver != 'v' && volver != 'V'){
            scanf(" %c", &volver);
        }
    }
}

/*  Función que procesa la salida del programa
 *  @return /O señal de retorno al programa     */
int salir(){
    char salida = 0;
    system(CLEAR);
    printf(BOLD"\n\nDESEA SALIR?\n\n"R_RESET
    BU_RED  "S"R_RESET B_RED  "i"R_RESET" \t(Introduzca \"S\")\n"
    BU_GREEN"N"R_RESET B_GREEN"o"R_RESET" \t(Introduzca \"N\")\n"
    UNDERL"I"R_RESET "nfo\t(Introduzca \"I\")\n");
    scanf(" %[sSnNiI]",&salida);
    if(salida == 's' || salida == 'S'){
        exit(1);
    }else{
        if(salida == 'i' || salida == 'I'){
            return mostrarInfo();
        }
    }
    return 1;
}

/*  Función que muestra información sobre el programa
 *  @return /O señal de retorno al programa     */
int mostrarInfo(){
    char salida = 0;

    system(CLEAR);
    printf("\nPrograma realizado por Albert Tambwe Miñón Apr/2025"
    "\nPara Progrmación - Ingeniería Informática - UBU\n\n"
    U_CYAN"https://github.com/filete/C-Matrix-Program-For-Semana-Santa.git\n"R_RESET);

    printf("\nIntroduzca "UNDERL"V"R_RESET" para cerrar la información.\n\n");
    while(salida != 'v' && salida != 'V'){
        scanf(" %c", &salida);
    }
    return 1;
}
## Información
Programa en C para la asignatura de __Programación__, __Grado en Ingeniería Informática__ de la __UBU__.
Realizado por Albert Tambwe Miñón entre _14 y 15 abril 2025_

#### <ins>Contenidos</ins>
__matrixProgram.c__ → Programa original.

__lab9_atm1024.c__ → Programa comentando cada función con el código limpio de comentarios innecesarios y funciones de depurado.

__colorGuide.h__ → Fichero cabecera para facilitar el uso de estilos ANSI, siéntase libre de usarlo.

__matriz.txt__ → Fichero que contiene una M<sub>4</sub> para poderse usar en los apartados 1 y 3.
___
#### <ins>Anotaciones</ins>
Algunas de las funciones están en inglés, y otras en español debido a que la mayoría del contenido que consumo está en inglés, por lo que algunos términos me resultan más sencillos de comprender y asociar en inglés. Esto tambiés se puede ver en el título de los commits.

El control de versiones no lo controlo demasiado toadavía, por lo que las prácticas empleadas no serán las mejores.
Algun commit puede ser un tanto innecesario, ya que los he estado usando como un sistema de guardado y transferencia entre equipos. De esta forma he podido experimentar el desarrollo en Linux con nvim y el windows con nvim y Fleet.

Ninguna herramienta de IA ha sido usada durante el desarrollo del programa, ni generativa, ni QOL como inline autocomplete generativo.
Únicamente se ha usado el autocomplado estático nativo de fleet y [nvim-cmp](https://github.com/hrsh7th/nvim-cmp).
___
Crear un programa que:
###  1. Llame a una función para leer una matriz *M1* de 4 filas y 4 columnas desde un archivo "matriz.txt" con por ejemplo los siguiengtes datos:


| x | y | z | w |
|---|---|---|---|
|1|10|100|0.1|
|2|20|200|0.2|
|3|30|300|0.3|
|4|40|400|0.4|
- [x] Terminado
___
### 2. Llame a una función para leer una matriz _M2_ 4x4, desde el teclado
- [x] Terminado
___
### 3. Presenta un menú con las oopciones y pida una opción
- - [x] a) Mostrar matriz M1
- - [x] b) Mostrar matriz M2
- - [x] c) Calcular MR = M1 + M2
- - [x] d) Calcular MR = M1 x M2
- - [x] e) Mostrar matriz MR
- - [x] f) Guardar matriz MR (en archivo _"resultado.txt"_ )
- - [x] g) Calcular y mostrar determinante
- - [x] z) Salir

- [x] Terminado
___
### 4. Llame a una función que resuelva la opción seleccionada o salir del programa
 - [x] Terminado
___
### 5. Vuelva al paso _3_
- [x] Terminado
___
### EXTRA
- [x] Añadir ventana de información.
___
#### <ins>Cosas a tener en cuenta</ins>
> ~~Tendré que crear una función para que se guarde la matriz en el fichero _'resultado.txt'_~~
- [x] Cambiar colores [Negro R/B/BU_BLACK]
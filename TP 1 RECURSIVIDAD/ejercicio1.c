#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "TP1_Recursividad.h"

const int TAM_MAX = 100;
const int TAM_MAX_AUX = 200;

// funcion para saber si una palabra es palindromo de manmera recursiva
bool palindromoRecursivo(char *cadena, int principio, int final) {
    if (cadena[principio] != cadena[final]) { // caso base
        return false;
    } else {
        if (final <= principio) { // caso base
            return true;
        } else {
            palindromoRecursivo(cadena, ++principio, --final); // caso recursivo
        }
    }
}

// funcion para saber si una palabra es palindromo
bool palindromo(char *cadena) {
    int principio = 0;
    int final = strlen(cadena) - 1;
    return palindromoRecursivo(cadena, principio, final);
}

int main() {
    char cadena[TAM_MAX + 1]; // se le agrega uno por el caracter nulo
    char cadenaAux[TAM_MAX_AUX + 1]; // se le agrega uno por el caracter nulo
    printf("Ingrese una cadena: ");
    fgets(cadenaAux, sizeof(cadenaAux), stdin); // utiliza la funcion fgets para leer una linea de texto desde la entrada. stdin es el flujo de entrada estandar, que generalmente esta asociado con la entrada del teclado
    cadenaAux[strlen(cadenaAux)-1] = '\0'; // elimina el caracter de nueva linea si existe

    // validado de que no supere el tamaño maximo
    while (strlen(cadenaAux) > TAM_MAX) {
        memset(cadenaAux, '\0', sizeof(cadenaAux)); // inicializo la cadena
        printf("La cadena tiene mas de %d caracteres, ingrese una cadena mas corta. ", TAM_MAX);
        printf("Ingrese una cadena: ");
        fgets(cadenaAux, sizeof(cadenaAux), stdin); // utiliza la funcion fgets para leer una linea de texto desde la entrada. stdin es el flujo de entrada estandar, que generalmente esta asociado con la entrada del teclado
        cadenaAux[strcspn(cadenaAux, "\n")] = '\0'; // elimina el caracter de nueva linea si existe
    }

    // si es valido y llega aca, se le asigna cadenaAux a cadena
    strcpy(cadena, cadenaAux); // cadena_destino, cadena_origen

    // se pasa a lowercase para la comparacion
    for (int i = 0; (i < strlen(cadena)); i++){
        cadena[i] = tolower(cadena[i]);
    }

    // si la cadena es vacia se avisa, pero se evalua de todas maneras (no se considera palindromo si es vacia)
    if ((strlen(cadena)) == 0) {
        printf("Cadena vacia.");
    } else {
        if (palindromo(cadena)) {
            printf("Es palindromo.");
        } else {
            printf("No es palindromo.");
        }
    }
    return 0;
}
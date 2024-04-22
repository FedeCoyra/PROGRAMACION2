#include "tipo_elemento.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "tp_pilas.h"

#include "pilas_punteros.c"
//#include "pilas_arreglos.c"

// funcion que copia una pila sin alterar la original
Pila copiar_pila(Pila pilaOriginal) {
    Pila pilaAuxiliar = p_crear();
    Pila pilaCopia = p_crear();
    while (!p_es_vacia(pilaOriginal)) {
        TipoElemento elemento = p_desapilar(pilaOriginal);
        p_apilar(pilaAuxiliar, elemento);
    }
    while (!p_es_vacia(pilaAuxiliar)) {
        TipoElemento elemento = p_desapilar(pilaAuxiliar);
        p_apilar(pilaOriginal, elemento);
        p_apilar(pilaCopia, elemento);
    }
    return pilaCopia;
}

// funcion que elimina de una pila un elemento segun su clave de manera ITERATIVA -> O(n)
// Pila p_ej6_eliminarclave(Pila p, int clave) {
//     if (p_es_vacia(p)) {
//         return p;
//     }

//     Pila Paux = p_crear();
//     TipoElemento elemento;

//     while(!p_es_vacia(p)) { // n
//         elemento = p_desapilar(p);
//         if (clave != elemento->clave){
//             p_apilar(Paux, elemento);
//         }
//     }

//     while (!p_es_vacia(Paux)) { // n
//         p_apilar(p, p_desapilar(Paux));
//     }

//     return p;
// }

// funcion que elimina un elemento de la pila RECURSIVAMENTE -> O(n)
Pila p_ej6_eliminarclave(Pila p, int clave) {
    if (p_es_vacia(p)) {
        return p;
    }

    TipoElemento elemento = p_desapilar(p);
    p_ej6_eliminarclave(p, clave);

    if (clave != elemento->clave) {
        p_apilar(p, elemento);
    }

    return p;
}

// funcion que carga de manera aleatoria una pila ingresada por parametro
void cargar_random(Pila P) {
    for (int i = 0; i < TAMANIO_MAXIMO; i++) {
        p_apilar(P, te_crear(rand()%5));
    }
}

// funcion que elimina los espacios de una cadena de char ingresada
void strtrim(char *cadena) {
    char *comienzoDeCadena = cadena;
    char *finalDeCadena = cadena + strlen(cadena) - 1;
    while (isspace(*comienzoDeCadena)) {
        comienzoDeCadena++;
    }
    while (isspace(*finalDeCadena) && finalDeCadena >= comienzoDeCadena) {
        finalDeCadena--;
    }
    *(finalDeCadena + 1) = '\0';
    memmove(cadena, comienzoDeCadena,   finalDeCadena - comienzoDeCadena + 2);
}

// funcion para leer un entero por teclado (validacion)
int leer_entero() {
    char entrada[100];
    long numero;
    char *finptr;
    int valido = 0;

    while (!valido) {
        printf("Ingrese un numero entero: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1] = '\0';
        strtrim(entrada);
        if (entrada[0] == '\0') {
            printf("Entrada invalida. Intentelo de nuevo.\n");
            continue;
        }
        errno = 0;
        numero = strtol(entrada, &finptr, 10);
        if (errno != 0 || *finptr != '\0' || numero > 100000 || numero < -100000) {
            printf("Entrada invalida (rango entero de -100k a 100k). Intentelo de nuevo.\n");
        } else {
            valido = 1;
        }
    }
    return (int) numero;
}

void main() {
    // cargo y muestro la pila original
    Pila P = p_crear();
    cargar_random(P);
    printf("[PILA ORIGINAL]\n");
    p_mostrar(P);
    printf("\n");

    // copio la pila original para no perderla y procedo a eliminar la clave pedida
    printf("[ELIMINAR]\n");
    Pila nuevaPila = copiar_pila(P);
    int n = leer_entero();
    printf("Eliminando elemento/s con clave %d\n", n);
    p_mostrar(p_ej6_eliminarclave(nuevaPila, n));
    printf("\n");

    // muestro pila original nuevamente para demostrar que no se perdio
    printf("[PILA ORIGINAL]\n");
    p_mostrar(P);
    printf("\n");
}
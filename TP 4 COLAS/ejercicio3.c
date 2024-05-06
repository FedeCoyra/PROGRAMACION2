#include "tipo_elemento.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "colas.h"

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

// funcion que rellena una cola por teclado
Cola rellenar_cola_por_teclado() {
    Cola cola = c_crear();
    int longitudCola = 0;
    printf("Ingrese la longitud de la cola (si se intenta superar el tamanio maximo, se dejaran de agregar elementos). ");
    longitudCola = leer_entero();
    while (longitudCola <= 0) {
        printf("Error. Ingrese la longitud de la cola nuevamente. ");
        longitudCola = leer_entero();
    }
    for (int i = 0; i < longitudCola; i++) {
        int ingreso = 0;
        printf("Ingrese el elemento %d. ", i + 1);
        ingreso = leer_entero();
        TipoElemento elemento = te_crear(ingreso);
        if (!c_encolar(cola, elemento)) {
            printf("No se pudo agregar el elemento debido a que la estructura esta llena.\n");
            printf("Se dejaran de agregar elementos y se trabajara con la cola actual.\n");
            break;
        }
    }
    return cola;
}

// funcion que pide una cola y retorna su longitud
int longitud_cola(Cola cola) {
    Cola colaAuxiliar = c_crear();
    int longitud = 0;
    while (!c_es_vacia(cola)) {
        TipoElemento elemento = c_desencolar(cola);
        c_encolar(colaAuxiliar, elemento);
        longitud++;
    }
    while (!c_es_vacia(colaAuxiliar)) {
        TipoElemento elemento = c_desencolar(colaAuxiliar);
        c_encolar(cola, elemento);
    }
    return longitud;
}

// funcion que compara dos colas para saber si son iguales o distintas (no perder las colas originales)
bool c_ej3_iguales(Cola c1, Cola c2) {
    Cola colaAuxiliar = c_crear();
    bool sonIguales = true;
    if (longitud_cola(c1) != longitud_cola(c2)) {
        return false;
    }
    TipoElemento elemento1, elemento2;
    while (!c_es_vacia(c1)) {
        c_encolar(colaAuxiliar, c_desencolar(c1));
    }
    while (!c_es_vacia(colaAuxiliar)) {
        elemento1 = c_desencolar(colaAuxiliar);
        elemento2 = c_desencolar(c2);
        if (elemento1->clave != elemento2->clave) {
            sonIguales = false;
        }
        c_encolar(c1, elemento1);
        c_encolar(c2, elemento2);
    }
    return sonIguales;
}

int main() {
    // INGRESO DE DATOS Y VALIDACION
    printf("[INGRESO DE DATOS]\n");
    // C1
    printf("= COLA1\n");
    Cola cola1 = rellenar_cola_por_teclado();
    // C2
    printf("= COLA2\n");
    Cola cola2 = rellenar_cola_por_teclado();
    // EJERCICIO
    printf("Mostrando COLA1: \n");
    c_mostrar(cola1);
    printf("Mostrando COLA2: \n");
    c_mostrar(cola2);
    c_ej3_iguales(cola1, cola2) ? printf("LAS COLAS SON IGUALES.\n") : printf("LAS COLAS SON DISTINTAS.\n");
    c_mostrar(cola1);
    c_mostrar(cola2);
    return 0;
}
#include "tipo_elemento.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "colas.h"

// funcion que pide una cola y se hace su copia sin alterar la version original
Cola copiar_cola(Cola colaOriginal) {
    Cola colaAuxiliar = c_crear();
    Cola colaCopia = c_crear();
    while (!c_es_vacia(colaOriginal)) {
        TipoElemento elemento = c_desencolar(colaOriginal);
        c_encolar(colaAuxiliar, elemento);
    }
    while (!c_es_vacia(colaAuxiliar)) {
        TipoElemento elemento = c_desencolar(colaAuxiliar);
        c_encolar(colaCopia, elemento);
        c_encolar(colaOriginal, elemento);
    }
    return colaCopia;
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

// funcion que toma una cola y retorna en otra todos los valores no repetidos
Cola c_ej4_colanorepetidos(Cola c) {
    Cola colaOriginal = copiar_cola(c);
    Cola colaSinRepetidos = c_crear();
    while (!c_es_vacia(colaOriginal)) {
        TipoElemento elementoOriginal = c_desencolar(colaOriginal);
        int contador = 0;
        Cola colaAuxiliar = copiar_cola(c);
        while (!c_es_vacia(colaAuxiliar)) {
            TipoElemento elementoAuxiliar = c_desencolar(colaAuxiliar);
            if (elementoOriginal->clave == elementoAuxiliar->clave) {
                contador++;
            }
        }
        if (contador <= 1) {
            c_encolar(colaSinRepetidos, elementoOriginal);
        }
    }
    return colaSinRepetidos;
}

int main() {
    printf("[INGRESO DE LA COLA]\n");
    Cola cola = rellenar_cola_por_teclado();
    printf("\n---------------------\n");
    printf("[COLA INGRESADA]\n");
    c_mostrar(cola);
    printf("[COLA SIN REPETIDOS]\n");
    c_mostrar(c_ej4_colanorepetidos(cola));
    return 0;
}
#include "colas.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static const int TAMANIO_MAXIMO_COLAS = 2001;

struct ColaRep {
    TipoElemento *valores;
    unsigned int frente;
    unsigned int final;
};


// Funcion interna que hace avanzar el frente y el final hacia adelante
int paso(int posicion) { // O(1)
    return ((posicion % TAMANIO_MAXIMO_COLAS) + 1);
}


Cola c_crear() { // O(1)
    Cola nueva_cola = (Cola) malloc(sizeof(struct ColaRep));
    // TODO hacer flexible y que la lista crezca sola
    nueva_cola->valores = calloc((TAMANIO_MAXIMO_COLAS + 1), sizeof(TipoElemento));
    //  Esto es fundamental ya que esta vacia si hacemos un paso con el final y nos encontramos con el frente
    nueva_cola->frente = 1;
    nueva_cola->final = TAMANIO_MAXIMO_COLAS;
    return nueva_cola;
}


bool c_encolar(Cola cola, TipoElemento elemento) { // O(1)
    if (c_es_llena(cola)) {
        return false;
    }
    cola->final = paso(cola->final);
    cola->valores[cola->final] = elemento;
    return true;
}


TipoElemento c_desencolar(Cola cola) { // O(1)
    int i;
    if (c_es_vacia(cola)) {
        return NULL;
    }
    TipoElemento elemento = cola->valores[cola->frente];
    cola->frente = paso(cola->frente);
    return elemento;
}


bool c_es_vacia(Cola cola) { // O(1)
    return (paso(cola->final) == cola->frente);
}


bool c_es_llena(Cola cola) { // O(1)
    return (paso(paso(cola->final)) == cola->frente);
}


void c_mostrar(Cola cola) { // O(n)
    if (c_es_vacia(cola)) {
        printf("COLA VACIA !!! \n");
        return;
    }

    Cola Caux = c_crear();
    TipoElemento X = te_crear(0);

    printf("-------------------------------------\n");
    printf("Imprimiendo las Claves de la Cola \n");
    printf("-------------------------------------\n");

    // La cola se debe desencolar y guardar en una auxiliar
    while (c_es_vacia(cola) != true) {
        X = c_desencolar(cola);
        printf("Clave:  %d \n", X->clave);
        c_encolar(Caux, X);
    }

    // ahora paso la auxiliar a la cola de nuevo para dejarla como estaba
    while (c_es_vacia(Caux) != true) {
        X = c_desencolar(Caux);
        c_encolar(cola, X);
    }

    printf("\n");
}


TipoElemento c_recuperar(Cola cola) { // O(1)
    TipoElemento X;
    if (c_es_vacia(cola)) {
        X = NULL;
    }
    else {
        X = cola->valores[cola->frente];
    }
}



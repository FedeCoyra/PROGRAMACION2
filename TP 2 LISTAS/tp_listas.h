#ifndef TP_LISTAS
#define TP_LISTAS

#include <stdbool.h>
#include "tipo_elemento.h"

struct ListaRep;
typedef struct ListaRep *Lista;
typedef enum{MAYOR,MENOR,IGUAL} resultadoCMP; // ej4

// ejercicio 2
Lista valoresFaltantesL1(Lista lista1, Lista lista2); // a
Lista valoresFaltantesL2(Lista lista1, Lista lista2); // b
Lista valoresComunes(Lista lista1, Lista lista2); // c
char * promediosListas(Lista lista1, Lista lista2); // d
char * maximoPosicionListas(Lista lista1, Lista lista2); // e

// ejercicio 3
bool multiploLista (Lista l1, Lista l2);

// ejercicio 4
resultadoCMP comparar(Lista L1, Lista L2);

// ejercicio 5
float calcular_polinomio(Lista lista, float x); // a
Lista calcular_intervalo(Lista lista, float minX, float maxX, float intervaloI); // b

// ejercicio 6
bool es_sublista (Lista principal, Lista secundaria);


#endif
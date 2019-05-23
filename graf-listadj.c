#include <stdio.h>
#include <stdlib.h>
#include "parametros.h"
#include "graf-listadj.h"

int adicionarAresta (LISTAADJ *l, int y) {
	LISTAADJ aux, ant;
	LISTAADJ novo;
	
	int status = 0;
	
	if (y > VERTICES)
		return status;
	
	novo = (LISTAADJ) malloc (sizeof (struct __noh_adj));
	if (novo == NULL) {
		printf("Falta de memoria\n");
		exit(1);
	}
	novo->vertice = y;
	novo->prox = NULL;
	
	aux = *l;
	ant = NULL;
	
	while ((aux != NULL) && (aux->vertice < y)) {
		ant = aux;
		aux = aux->prox;
	}
	
	if (ant == NULL) {// 1o elemento
		*l = novo;
		novo->prox = aux;
		status = 1;
	} else {
		if (aux == NULL) {// final da lista
			ant->prox = novo;
			status = 1;
		} else {
			if (aux->vertice != y) {// Meio da lista e nao existe
				ant->prox = novo;
				novo->prox = aux;
				status = 1;
			} else 
				free (novo);
		}
	}
	
	return status;
}


void mostraGrafoLista (LISTAADJ *l, int numVertices) {
	int x;
	LISTAADJ t;
	
	printf("Lista de adjacencias\n");
	for (x = 0; x < numVertices; x++) {
		printf("Vertice %2d: ", x);
		t = l[x];
		while (t != NULL) {
			printf("%2d ", t->vertice);
			t = t->prox;
		}
		printf("\n");
	}
	
	return;   
}

int grausLista(LISTAADJ *l, int numVertices, int v, int *gE, int *gS) {
	
	int x;
	LISTAADJ t;
	
	if ((v > VERTICES) || (v < 0))
		return 0;
	
	*gE = 0;
	*gS = 0;
	
	for (x = 0; x < numVertices; x++) {
		t = l[x];
		while (t != NULL) {
			if (t->vertice == v)
				*gE = *gE + 1;
			if (x == v)
				*gS = *gS + 1;
			t = t->prox;
		}
	}
	
	return 1;
}

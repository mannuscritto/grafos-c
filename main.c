#include <stdio.h>
#include <stdlib.h>
#include "parametros.h"
#include "graf-listadj.h"
#include "graf-matrizadj.h"

int main(int argc, char *argv[]) {
	short MATRIZ[VERTICES][VERTICES];
	LISTAADJ ADJACENCIAS[VERTICES];
	
	int numVertices = 0;
	int x, y;
	int gS, gE;
	
	for (x = 0; x < VERTICES; x++) {
		ADJACENCIAS[x] = NULL;
		for (y = 0; y < VERTICES; y++)
			MATRIZ[x][y] = 0;
	}
	
	while (1) {
		printf("Digite a origem e o destino da aresta: ");
		scanf("%d %d", &x, &y);
		if ((x == -1) || (y == -1))
			break;
		if ((x >= 0) && (x < VERTICES) && (y >= 0) && (y < VERTICES)) {
			MATRIZ[x][y] = 1;
			adicionarAresta (&ADJACENCIAS[x], y);
			if (x > numVertices)
				numVertices = x;
			if (y > numVertices)
				numVertices = y;
		}
	}
	numVertices = numVertices + 1;
	
	mostraGrafo (MATRIZ, numVertices);
	mostraGrafoLista (ADJACENCIAS, numVertices);
	
	printf(" V  gE  gS\n");
	for (x = 0; x < numVertices; x++) {
		graus(MATRIZ, x, &gE, &gS);
		printf("%2d %3d %3d\n", x, gE, gS);
	}
	
	printf(" V  gE  gS\n");
	for (x = 0; x < numVertices; x++) {
		grausLista(ADJACENCIAS, numVertices, x, &gE, &gS);
		printf("%2d %3d %3d\n", x, gE, gS);
	}
	
	system("PAUSE");	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(int argc, char *argv[]) {
	TipoGrafo Grafo;
	
	int numVertices = 10;
	int x, y, peso;
	int gS, gE;
		
	if (!FGVazio(&Grafo, numVertices)) {
		printf("Erro ao criar novo grafo!\n");
		exit(1);
	}
	
	while (1) {
		printf("Digite a origem, o destino e o peso da aresta: ");
		scanf("%d %d %d", &x, &y, &peso);
		if ((x == -1) || (y == -1) || (peso == -1))
			break;
		if (!InsereAresta(x, y, peso, &Grafo, 0)) {
			printf("Erro ao inserir aresta!\n");
			exit(2);
		}
	}
	numVertices = numVertices + 1;
	
	ImprimeGrafo(&Grafo);
	
	printf("Matriz de adjacencias\n");
	printf(" V  gE  gS\n");
	for (x = 0; x < numVertices; x++) {
		ObterGrauNo(x, &Grafo, &gE, &gS);
		printf("%2d %3d %3d\n", x, gE, gS);
	}
	
	PercursoBFS bfs;
	printf("Percurso de largura\n");
	PercursoLargura (0, &Grafo, &bfs);
	printf("Origem %d tem %d destinos\n", bfs.Origem, bfs.NumDestinos);
	printf(" V  cor  dist  pai\n");
	for (x = 0; x < bfs.NumDestinos; x++) {
		printf("%2d %3d %3d %3d\n", x, bfs.vertex[x].cor, bfs.vertex[x].distancia, bfs.vertex[x].pai);
	}
	
	system("PAUSE");	
	return 0;  
}

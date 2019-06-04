#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(int argc, char *argv[]) {
	TipoGrafo grafo;
	PercursoBFS percurso;
	PercursoDFS percurso2;
	int x, y, z, max;
	unsigned gE, gS;
	
	do {
		printf("Digite a quantidade de vertices: ");
		scanf("%d", &max);	
	} while (max <= 0 || max > MAXNUMVERTICES);
	
	if (!FGVazio(&grafo, max)) {
		printf("Problemas para criar o grafo\n");
		exit(1);
	}

	for (y = 0; y < grafo.MaxVertices; y++) {
		printf("Digite o rotulo do vertice %d: ", y+1);
		scanf("%s", grafo.label[y]);
		if (grafo.label[y][0] != 0) {
			grafo.NumVertices = grafo.NumVertices + 1;
		} else {
			break;
		}
	}

	while (1) {
		printf("Digite a origem, o destino e o peso da aresta: ");
		scanf("%d %d %d", &x, &y, &z);
		if ((x == -1) || (y == -1) || (z == -1))
			break;
		if (!InsereAresta(x, y, z, &grafo, 1))
			printf("Nao foi possivel inserir a aresta\n");
	}
	
	ImprimeGrafo(&grafo);
	
	PercursoProfundidade (0, &grafo, &percurso2, 1);
	printf("  V Cor Des Ter Pai\n");
	for (y = 0; y < grafo.MaxVertices; y++)
		printf("%3s %3d %3d %3d %3d\n", grafo.label[y], 
											percurso2.vertex[y].cor,
											percurso2.vertex[y].descoberta,
											percurso2.vertex[y].termino,
											percurso2.vertex[y].pai);
	
	if (percurso2.DAG) {
		printf("Ordem Topologica: ");
		for (y = 0; y < percurso2.NumDestinos; y++) {
			printf("%s ", grafo.label[percurso2.OrdemTopologica[y]]);
		}
		printf("\n");
	}
	
	system("PAUSE");
	return 0;
}

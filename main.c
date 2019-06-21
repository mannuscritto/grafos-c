#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "grafo.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	
	TipoGrafo grafo;
	PercursoBFS bfs;
	PercursoDFS percurso2;
	AlgoritmoDijkstra algd;
	int opt, x, y, z, max, origem, destino;
	unsigned gE, gS;
	
	while (1) {
		system("CLS");
		
		printf("\t\tMENU - MAPA EM GRAFO\n\n");
		printf("\tAdicionar Vértice...[1]\n");
		printf("\tAdicionar Aresta....[2]\n");
		printf("\tRemover Aresta......[3]\n");
		printf("\tImprimir Grafo......[4]\n");
		printf("\tPercurso BFS........[5]\n");
		printf("\tPercurso DFS........[6]\n");
		printf("\tMelhor caminho......[7]\n");
		printf("\tSair................[0]\n");
		printf("\nDigite a opção: ");
		do {
			scanf("%d", &opt);	
		} while (opt < 0 || opt > 8);
		switch (opt) {
			case 0:
				exit(0);
				break;
			case 1:
				if (max == 0) {
					do {
						printf("Digite a quantidade de vértices: ");
						scanf("%d", &max);
					} while (max <= 0 || max > MAXNUMVERTICES);

					if (!FGVazio(&grafo, max)) {
						printf("Problemas para criar o grafo\n");
						exit(1);
					}
				}
				char temp[50];
				printf("Digite o rótulo do vértice %d: ", grafo.NumVertices+1);
				scanf(" %[^\n]", temp);
				grafo.label[grafo.NumVertices] = (char *) calloc (strlen(temp), sizeof(char));
				strcpy(grafo.label[grafo.NumVertices], temp);
				grafo.NumVertices = grafo.NumVertices + 1;
				break;
			case 2:
				printf("Digite a origem, o destino e o peso da aresta: ");
				scanf("%d %d %d", &x, &y, &z);
				if (!InsereAresta(x, y, z, &grafo, true))
					printf("Não foi possível inserir a aresta!\n");
				break;
			case 3:
				printf("Digite a origem e o destino da aresta: ");
				scanf("%d %d", &x, &y);
				if (!RetiraAresta(x, y, &z, &grafo, true)) {
					printf("Não foi possível remover a aresta!\n");
				} else {
					printf("Removida aresta com peso %d\n", z);
				}
				break;
			case 4:
				system("CLS");
				ImprimeGrafo(&grafo);
				break;
			case 5:
				printf("Digite o vértice de origem: ");
				scanf("%d", &origem);
				system("CLS");
				printf("\t\tPercurso de Largura\n\n");
				PercursoLargura(origem, &grafo, &bfs);
				printf("Origem %s tem %d destinos\n", grafo.label[bfs.Origem], bfs.NumDestinos);
				printf(" Ver Cor Dis Pai\n");
				for (x = 0; x < bfs.NumDestinos; x++) {
					printf("%3s %3d %3d %3s\n", grafo.label[x],
							bfs.vertex[x].cor, 
							bfs.vertex[x].distancia, 
							bfs.vertex[x].pai != -1 ? grafo.label[bfs.vertex[x].pai] : "-1");
				}
				break;
			case 6:
				printf("Digite o vértice de origem: ");
				scanf("%d", &origem);
				system("CLS");
				printf("\t\tPercurso de Profundidade\n\n");
				PercursoProfundidade(origem, &grafo, &percurso2, true);
				printf("Origem %s tem %d destinos\n", grafo.label[percurso2.Origem], percurso2.Origem);
				printf(" Ver Cor Des Ter Pai\n");
				for (y = 0; y < grafo.NumVertices; y++)
					printf("%3s %3d %3d %3d %3s\n", grafo.label[y], 
														percurso2.vertex[y].cor,
														percurso2.vertex[y].descoberta,
														percurso2.vertex[y].termino,
														percurso2.vertex[y].pai != -1 ? grafo.label[percurso2.vertex[y].pai] : "-1");
				
				if (percurso2.DAG) {
					printf("Ordem Topologica: ");
					for (y = 0; y < percurso2.NumDestinos; y++) {
						printf("%s ", grafo.label[percurso2.OrdemTopologica[y]]);
					}
					printf("\n");
				}
				break;
			case 7:
				printf("Digite o vértice de origem e o de destino: ");
				scanf("%d %d", &origem, &destino);
				system("CLS");
				printf("\t\tAlgoritmo de Dijkstra\n\n");
				executar(origem, destino, &algd, &grafo);
				printf("Melhor caminho entre vertices\nOrigem: %s\n", grafo.label[algd.Origem]);
				printf(" Ver Cor Dis Pre\n");
				for (y = 0; y < grafo.NumVertices; y++) {
					printf("%3s %3d %3d %3s\n", grafo.label[y],
													algd.vertex[y].cor,
													algd.vertex[y].dist,
													algd.vertex[y].prev != -1 ? grafo.label[algd.vertex[y].prev] : "-1");
				}
				break;
		}
		system("PAUSE");
	}

	system("PAUSE");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(int argc, char *argv[])
{
  TipoGrafo grafo;
  PercursoBFS percurso;
  PercursoDFS percurso2;
  int x, y, z;
  unsigned gE, gS;
  
  if (!FGVazio(&grafo, 8))
  {
     printf("Problemas para criar o grafo\n");
     exit(1);
  }

  while (1)
  {
     printf("Digite a origem, o destino e o peso da aresta: ");
     scanf("%d %d %d", &x, &y, &z);
     if ((x == -1) || (y == -1))
        break;
     if (!InsereAresta(x, y, z, &grafo, 1))
        printf("Nao foi possivel inserir a aresta\n");
  }

  ImprimeGrafo(&grafo);

  PercursoProfundidade (0, &grafo, &percurso2, 1);
  printf("  V Cor Des Ter Pai\n");
  for (y = 0; y < grafo.MaxVertices; y++)
      printf("%3d %3d %3d %3d %3d\n", y, percurso2.vertex[y].cor,
                                         percurso2.vertex[y].descoberta,
                                         percurso2.vertex[y].termino,
                                         percurso2.vertex[y].pai);
                                         
	
	if (percurso2.DAG) {
		printf("Ordem Topologica: ");
		for (y = 0; y < percurso2.NumDestinos; y++) {
			printf("%d ", percurso2.OrdemTopologica[y]);
		}
		printf("\n");
	}

  system("PAUSE");
  return 0;
}

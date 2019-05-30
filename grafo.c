#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

short FGVazio(TipoGrafo *Grafo, unsigned max)
{
  unsigned i, j;

  if ((max > MAXNUMVERTICES) || (max < 1))
  {
    return 0;
  }

  Grafo->MaxVertices = max;
  Grafo->NumVertices = 0;
  Grafo->NumArestas = 0;

  for (i = 0; i < Grafo->NumVertices; i++)
    for (j = 0; j < Grafo->NumVertices; j++)
    {
      Grafo->Mat[i][j] = 0;
    }

  return 1;
}

short InsereAresta(unsigned V1, unsigned V2, int Peso, TipoGrafo *Grafo,
                   short Direcionado)
{
  if ((Peso == 0) || (V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) ||
      (V1 < 0) || (V2 < 0) || (Grafo->NumArestas == MAXNUMARESTAS))
  {
    return 0;
  }

  Grafo->Mat[V1][V2] = Peso;

  if (!Direcionado)
  {
    Grafo->Mat[V2][V1] = Peso;
  }

  Grafo->NumArestas++;
  return 1;
}

short RetiraAresta(unsigned V1, unsigned V2, int *Peso, TipoGrafo *Grafo,
                   short Direcionado)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
  {
    return 0;
  }

  *Peso = Grafo->Mat[V1][V2];

  if (*Peso == 0)
  {
    return 0;
  }

  Grafo->Mat[V1][V2] = 0;

  if (!Direcionado)
  {
    Grafo->Mat[V2][V1] = 0;
  }

  Grafo->NumArestas--;
  return 1;
}

short ExisteAresta(unsigned V1, unsigned V2, TipoGrafo *Grafo)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
  {
    return 0;
  }

  return (Grafo->Mat[V1][V2] != 0);
}

void ImprimeGrafo(TipoGrafo *Grafo)
{
  unsigned i, j;
  printf("   ");

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    printf("%3d", i);
  }

  printf("\n");

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    printf("%3d", i);

    for (j = 0; j < Grafo->MaxVertices; j++)
    {
      printf("%3d", Grafo->Mat[i][j]);
    }

    printf("\n");
  }

  return;
}

int ObterPesoAresta(unsigned V1, unsigned V2, TipoGrafo *Grafo, int *Peso)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
  {
    return 0;
  }

  *Peso = Grafo->Mat[V1][V2];
  return 1;
}

short ObterListaAdjacencias(unsigned V1, TipoGrafo *Grafo,
                            TipoListaAdjGrafo *Lista)
{
  unsigned i;
  int peso;

  if ((V1 > Grafo->MaxVertices) || (V1 < 0))
  {
    return 0;
  }

  Lista->NumAdjacentes = 0;

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    if (ExisteAresta(V1, i, Grafo))
    {
      if (!ObterPesoAresta(V1, i, Grafo, &peso))
      {
        printf("Inconsistencia\n");
        exit(1);
      }

      Lista->Lista[Lista->NumAdjacentes][0] = i;
      Lista->Lista[Lista->NumAdjacentes][1] = peso;
      Lista->NumAdjacentes++;
    }
  }

  return 1;
}

short ObterGrauNo(unsigned V1, TipoGrafo *Grafo, unsigned *gE, unsigned *gS)
{
  unsigned i;

  if ((V1 > Grafo->MaxVertices) || (V1 < 0))
  {
    return 0;
  }

  *gE = 0;
  *gS = 0;

  for (i = 0; i < Grafo->MaxVertices; i++)
  {
    if (ExisteAresta(V1, i, Grafo))
    {
      *gS = *gS + 1;
    }

    if (ExisteAresta(i, V1, Grafo))
    {
      *gE = *gE + 1;
    }
  }

  return 1;
}

void PercursoLargura (unsigned V1, TipoGrafo *G, PercursoBFS *bfs) {
	unsigned i, u, v, inicio, final;
	unsigned * fila;
	TipoListaAdjGrafo adjacentes;
	if ((V1 > G->MaxVertices ) || (V1 < 0))
		return;
		
	fila = (unsigned *)calloc(G->MaxVertices, sizeof(unsigned));
	inicio = final = 0;
	
	for (i = 0; i < G->MaxVertices; i++){
		bfs->vertex[i].cor = BRANCO;
		bfs->vertex[i].distancia = -1;
		bfs->vertex[i].pai = -1;
	}
	
	bfs->Origem = V1;
	bfs->NumDestinos = 0;
	bfs->vertex[V1].cor = CINZA;
	bfs->vertex[V1].distancia = 0;
	
	fila[final++] = V1;
	while(inicio != final) {
		u = fila[inicio++];
		ObterListaAdjacencias(u, G, &adjacentes);
		for (i = 0; i < adjacentes.NumAdjacentes; i++) {
			v = adjacentes.Lista[i][0];
			if (bfs->vertex[v].cor == BRANCO) {
				bfs->vertex[v].cor = CINZA;
				bfs->vertex[v].distancia = bfs->vertex[u].distancia + 1;
				bfs->vertex[v].pai = u;
				fila[final++] = v;
			}  
		}
		bfs->vertex[u].cor = PRETO;
		bfs->NumDestinos = bfs->NumDestinos + 1;
	}
	free(fila);
	return;
}

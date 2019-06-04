#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "grafo.h"

bool FGVazio(TipoGrafo *Grafo, unsigned max)
{
  unsigned i, j;

  if ((max > MAXNUMVERTICES) || (max < 1))
  {
    return false;
  }

  Grafo->MaxVertices = max;
  Grafo->NumVertices = 0; /* Por enquanto, inutil */
  Grafo->NumArestas = 0;

  for (i = 0; i < Grafo->MaxVertices; i++)
    for (j = 0; j < Grafo->MaxVertices; j++)
    {
      Grafo->Mat[i][j] = 0;
    }

  return true;
}

bool InsereAresta(unsigned V1, unsigned V2, int Peso, TipoGrafo *Grafo,
                   bool Direcionado)
{
  if ((Peso == 0) || (V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) ||
      (V1 < 0) || (V2 < 0) || (Grafo->NumArestas == MAXNUMARESTAS))
  {
    return false;
  }

  Grafo->Mat[V1][V2] = Peso;

  if (!Direcionado)
  {
    Grafo->Mat[V2][V1] = Peso;
  }

  Grafo->NumArestas++;
  return true;
}

bool RetiraAresta(unsigned V1, unsigned V2, int *Peso, TipoGrafo *Grafo,
                   bool Direcionado)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
  {
    return false;
  }

  *Peso = Grafo->Mat[V1][V2];

  if (*Peso == 0)
  {
    return false;
  }

  Grafo->Mat[V1][V2] = 0;

  if (!Direcionado)
  {
    Grafo->Mat[V2][V1] = 0;
  }

  Grafo->NumArestas--;
  return true;
}

bool ExisteAresta(unsigned V1, unsigned V2, TipoGrafo *Grafo)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
  {
    return false;
  }

  return (Grafo->Mat[V1][V2] != 0);
}

void ImprimeGrafo(TipoGrafo *Grafo)
{
  unsigned i, j;
  printf("   ");

  for (i = 0; i < Grafo->NumVertices; i++)
  {
    printf("%3s", Grafo->label[i]);
  }

  printf("\n");

  for (i = 0; i < Grafo->NumVertices; i++)
  {
    printf("%3s", Grafo->label[i]);

    for (j = 0; j < Grafo->NumVertices; j++)
    {
      printf("%3d", Grafo->Mat[i][j]);
    }

    printf("\n");
  }

  return;
}

bool ObterPesoAresta(unsigned V1, unsigned V2, TipoGrafo *Grafo, int *Peso)
{
  if ((V1 > Grafo->MaxVertices) || (V2 > Grafo->MaxVertices) || (V1 < 0) ||
      (V2 < 0))
  {
    return false;
  }

  *Peso = Grafo->Mat[V1][V2];
  return true;
}

bool ObterListaAdjacencias(unsigned V1, TipoGrafo *Grafo,
                            TipoListaAdjGrafo *Lista)
{
  unsigned i;
  int peso;

  if ((V1 > Grafo->MaxVertices) || (V1 < 0))
  {
    return false;
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

  return true;
}

bool ObterGrauNo(unsigned V1, TipoGrafo *Grafo, unsigned *gE, unsigned *gS)
{
  unsigned i;

  if ((V1 > Grafo->MaxVertices) || (V1 < 0))
  {
    return false;
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

  return true;
}

void  PercursoLargura (unsigned V1, TipoGrafo *Grafo, PercursoBFS *bfs)
{
  unsigned i, u, v;
  unsigned *fila;
  int inicio, final;
  TipoListaAdjGrafo adjacentes;
  
  if ((V1 > Grafo->MaxVertices) || (V1 < 0))
    return;
  
  fila = (unsigned *) malloc (Grafo->MaxVertices * sizeof(unsigned));
  inicio = final = 0;
  
  for (i = 0; i < Grafo->MaxVertices; i++)
  {
     bfs->vertex[i].cor = BRANCO;
     bfs->vertex[i].pai = -1;
     bfs->vertex[i].distancia = -1;
  }
  
  bfs->Origem = V1;
  bfs->NumDestinos = 0;
  bfs->vertex[V1].cor = CINZA;
  bfs->vertex[V1].distancia = 0;
  
  fila[final++] = V1;
  
  while (inicio != final)
  {
     u = fila[inicio++];

     ObterListaAdjacencias(u, Grafo, &adjacentes);
     for (i = 0; i < adjacentes.NumAdjacentes; i++)
     {
        v = adjacentes.Lista[i][0];
        if (bfs->vertex[v].cor == BRANCO)
        {
           bfs->vertex[v].cor = CINZA;
           bfs->vertex[v].distancia = bfs->vertex[u].distancia + 1;
           bfs->vertex[v].pai = u;
           fila[final++] = v;
        }
     }
     bfs->vertex[u].cor = PRETO;
     bfs->NumDestinos = bfs->NumDestinos + 1;
  }

  free (fila);
  return;
}


void PercursoProfundidade (unsigned V1, TipoGrafo *Grafo, PercursoDFS *dfs, short todos)
{
  unsigned i;
  unsigned relogio;
  unsigned delta;
 
  for (i = 0; i < Grafo->MaxVertices; i++)
  {
     dfs->vertex[i].cor = BRANCO;
     dfs->vertex[i].pai = -1;
     dfs->vertex[i].descoberta = -1;
     dfs->vertex[i].termino = -1;
     dfs->OrdemTopologica[i] = -1;
  }
  dfs->Origem = V1;
  dfs->NumDestinos = 0;
  dfs->DAG = 1;

  relogio = -1;

	if (!todos) {
		_PP(V1, Grafo, dfs, &relogio, -1);		
	} else {
		for (i = 0; i < Grafo->NumVertices; i++) {
			if (dfs->vertex[i].cor == BRANCO)
				_PP(i, Grafo, dfs, &relogio, -1);
		}
	}
	
  if (dfs->DAG) {
  	delta = Grafo->NumVertices - dfs->NumDestinos;
  	
  	for (i = 0; i < dfs->NumDestinos; i++) {
  		dfs->OrdemTopologica[i]	= dfs->OrdemTopologica[i + delta];
	}
	for (; i < Grafo->NumVertices; i++) {
		dfs->OrdemTopologica[i] = -1;
	}
  }
  
  return;
}

void  _PP (unsigned vertice, TipoGrafo *Grafo, PercursoDFS *dfs,
           unsigned *relogio, unsigned pai)
{
   TipoListaAdjGrafo adjacentes;
   unsigned i, v;

   *relogio = *relogio + 1;
   dfs->vertex[vertice].cor = CINZA;
   dfs->vertex[vertice].descoberta = *relogio;

   ObterListaAdjacencias(vertice, Grafo, &adjacentes);
   for (i = 0; i < adjacentes.NumAdjacentes; i++)
   {
       v = adjacentes.Lista[i][0];
      
      switch (dfs->vertex[v].cor) {
		case BRANCO:// Aresta de arvore
			dfs->vertex[v].pai = vertice;
         	_PP (v, Grafo, dfs, relogio, vertice);
			break;
		case CINZA:// Aresta de retorno
			dfs->DAG = 0;
			break;
		case PRETO:// Aresta de avanco ou de cruzamento
			break;	
	  }
   }
   dfs->vertex[vertice].cor = PRETO;
   dfs->NumDestinos = dfs->NumDestinos + 1;
   *relogio = *relogio + 1;
   dfs->vertex[vertice].termino = *relogio;
   dfs->OrdemTopologica[Grafo->NumVertices - dfs->NumDestinos] = vertice;

   return;   
}

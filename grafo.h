#ifndef __GRAFOMATRIZ__
#define __GRAFOMATRIZ__

#include <stdbool.h>
#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500

typedef struct __TipoGrafo
{
  int Mat[MAXNUMVERTICES][MAXNUMVERTICES];
  char **label;
  unsigned MaxVertices;
  unsigned NumVertices;
  unsigned NumArestas;
} TipoGrafo;

typedef struct __TipoListaAdjGrafo
{
  unsigned Lista[MAXNUMVERTICES][2];
  unsigned NumAdjacentes;
} TipoListaAdjGrafo;

typedef enum
{
  BRANCO,
  CINZA,
  PRETO
} TipoCor;

typedef struct __RegistroLargura
{
  TipoCor cor;
  unsigned pai;
  unsigned distancia;
} RegistroLargura;

typedef struct __PercursoLargura
{
   RegistroLargura vertex[MAXNUMVERTICES];
   unsigned Origem;
   unsigned NumDestinos;
} PercursoBFS;

typedef struct __RegistroProfundidade
{
  TipoCor cor;
  unsigned pai;
  unsigned descoberta;
  unsigned termino;
} RegistroProfundidade;

typedef struct __PercursoProfundidade
{
   RegistroProfundidade vertex[MAXNUMVERTICES];
   unsigned Origem;
   unsigned NumDestinos;
   short DAG;
   unsigned OrdemTopologica[MAXNUMVERTICES];
} PercursoDFS;

typedef struct __RegistroDijkstra
{
  TipoCor cor;
  int prev;
  int dist;
} RegistroDijkstra;

typedef struct {
	RegistroDijkstra vertex[MAXNUMVERTICES];
	unsigned Origem;
	unsigned Destino;
	int NumProc;
} AlgoritmoDijkstra;

//Funcoes para algoritmo Dijkstra
void executar(unsigned, unsigned, AlgoritmoDijkstra *, TipoGrafo *);
bool encontrarDistanciasMinimas(AlgoritmoDijkstra *, TipoGrafo *, unsigned *);
void obterCaminho(AlgoritmoDijkstra *, TipoGrafo *);

bool FGVazio(TipoGrafo *, unsigned);
bool FreeGrafo(TipoGrafo *);
bool InsereAresta(unsigned, unsigned, int, TipoGrafo *, bool);
bool ExisteAresta(unsigned, unsigned, TipoGrafo *);
bool ObterPesoAresta(unsigned, unsigned, TipoGrafo *, int *);
bool RetiraAresta(unsigned, unsigned, int *, TipoGrafo *, bool);
bool ObterListaAdjacencias(unsigned, TipoGrafo *, TipoListaAdjGrafo *);
void ImprimeGrafo(TipoGrafo *);
bool ObterGrauNo(unsigned, TipoGrafo *, unsigned *, unsigned *);
void  PercursoLargura (unsigned, TipoGrafo *, PercursoBFS *);
void  PercursoProfundidade (unsigned, TipoGrafo *, PercursoDFS *, bool); 
void  _PP (unsigned, TipoGrafo *, PercursoDFS *, unsigned *, unsigned);
#endif

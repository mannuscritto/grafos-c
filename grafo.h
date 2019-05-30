#ifndef __GRAFOMATRIZ__
#define __GRAFOMATRIZ__

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500

typedef struct __TipoGrafo
{
  int Mat[MAXNUMVERTICES][MAXNUMVERTICES];
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

typedef struct __RegistrarLargura {
	TipoCor cor;
	unsigned pai;
	unsigned distancia;
} RegistroLargura;

typedef struct __PercursoLargura {
    RegistroLargura vertex[MAXNUMVERTICES];
    unsigned Origem;
    unsigned NumDestinos;
} PercursoBFS;

void PercursoLargura (unsigned, TipoGrafo *, PercursoBFS *);
short FGVazio(TipoGrafo *, unsigned);
short InsereAresta(unsigned, unsigned, int, TipoGrafo *, short);
short RetiraAresta(unsigned, unsigned, int *, TipoGrafo *, short);
short ExisteAresta(unsigned, unsigned, TipoGrafo *);
int   ObterPesoAresta(unsigned, unsigned, TipoGrafo *, int *);
short ObterListaAdjacencias(unsigned, TipoGrafo *, TipoListaAdjGrafo *);
void  ImprimeGrafo(TipoGrafo *);
short ObterGrauNo(unsigned, TipoGrafo *, unsigned *, unsigned *);

#endif

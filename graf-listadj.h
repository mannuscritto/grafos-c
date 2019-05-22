#ifndef __GRAFLISTA__
#define __GRAFLISTA__
struct __noh_adj
{
   int vertice;
   struct __noh_adj *prox;
};

typedef struct __noh_adj * LISTAADJ;

int adicionarAresta (LISTAADJ *, int);   // elemento do vetor (x) e destino (y)
void mostraGrafoLista (LISTAADJ *, int); // vetor de listas e max vertice
int grausLista(LISTAADJ *, int, int, int *, int *);

#endif

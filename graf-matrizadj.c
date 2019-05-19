#include <stdio.h>
#include <stdlib.h>
#include "parametros.h"
#include "graf-matrizadj.h"

void mostraGrafo (short GRAFO[VERTICES][VERTICES], int numVertices)
{
   int x, y;

   printf("d/p  ");
   for(x = 0; x < numVertices; x++)
      printf("%2d ", x);
   printf("\n");
   
   for(x = 0; x < numVertices; x++)
   {
     printf(" %2d: ", x);
     for (y = 0; y < numVertices; y++)
       printf("%2d ", GRAFO[x][y]);
     printf("\n");
   }
   return;
}


int graus(short GRAFO[VERTICES][VERTICES], int v, int *gE, int *gS)
{
  int x;
  
  if ((v > VERTICES) || (v < 0))
    return 0;
  
  *gE = 0;
  *gS = 0;
  
  for (x = 0; x < VERTICES; x++)
  {
    if (GRAFO[v][x] == 1)
       *gS = *gS + 1;
    if (GRAFO[x][v] == 1)
       *gE = *gE + 1;
  }
    
  return 1;
}

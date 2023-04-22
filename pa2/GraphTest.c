// ========== Name ========== //
// Manikantanagasai H. Illuri //
// milluri@ucsc.edu           //
// 2023 Spring CSE101         //
// PA 2                       //
// Testing ADT Functions      //
// ========================== //
// I have added more of my own tests to 
/****************************************************************************************
*  GraphTest.c
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  C = newList(); 
   List  P = newList(); 
   List  E = newList();
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   printf("%s\n", "AddEdge test");
   addEdge(G, 9, 31);
   addEdge(G, 10, 31);
   addEdge(G, 8, 31);
   addEdge(G, 13, 31);
   addEdge(G, 16, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);
   printf("%s\n", "AddEdge test DONE");

   // Print adjacency list representation of G
   printf("%s\n", " Print adjacency list representation of Graph DONE");
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 6);
   append(P, 6);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=8; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);
}
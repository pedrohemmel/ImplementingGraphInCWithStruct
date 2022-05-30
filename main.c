#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/*STRUCTS*/
//Defining the properties of the whole Graph
struct graph {
  int isWeighted;
  int numOfVertices;
  int maxGrade;

  //Creating the variables with pointers
  int **edges;
  float **weights;
  int *grade;
};

/*FUNCTIONS*/
//Function that will struture a new graph with values
Graph *createNewGraph(int numOfVertices, int maxGrade, int isWeighted) {
  
  //Initializing a new Graph with malloc
  Graph *newGraph = (Graph *)malloc(sizeof(struct graph));

  //Defining the values of the properties
  newGraph->numOfVertices = numOfVertices;
  newGraph->maxGrade = maxGrade;
  //Verifying if the weight is diferent of 0, if it is, isWeighted is equal of 1, else, is equal of 0
  newGraph->isWeighted = (isWeighted != 0)?1:0;
  //Storing the number of index that this graph will have, it was used calloc because initially, each vertice has 0 as grade value
  newGraph->grade = (int *)calloc(numOfVertices, sizeof(int));

  //Defining the number of vertices in the edges e setting how many edges each vertice has
  newGraph->edges = (int**)malloc(numOfVertices*sizeof(int *));
  //For each vertice, is created a list of grades
  for(int i = 0; i < numOfVertices; i++) {
    newGraph->edges[i] = (int *)malloc(maxGrade*sizeof(int));
  }
  
  if(newGraph->isWeighted) {
    newGraph->weights = (float **)malloc(numOfVertices*sizeof(float*));
    //For each vertice, is created a list of grades
    for(int i = 0; i < numOfVertices; i++) {
      newGraph->weights[i] = (float *)malloc(maxGrade*sizeof(float));
    }
  }

  return newGraph;
} 

//Function that will insert new edges in the graph
int insertingEdges(Graph *newGraph, int origin, int destiny, int isDigraph, float weight) {

  //Verifying if the parameters are right
  if(newGraph == NULL) {
    return 0;
  } 
  if(origin < 0 || origin >= newGraph->numOfVertices) {
    return 0;
  }
  if(destiny < 0 || destiny >= newGraph->numOfVertices) {
    return 0;
  }

  //Inserting value of destiny in the actual edge
  newGraph->edges[origin][destiny] = 1;

  //Inserting value of weight in the actual edge
  if(newGraph->isWeighted) {
    newGraph->edges[origin][destiny] = weight;
  }
  newGraph->grade[origin]++;

  //Verifying if is digraph, if it is, it's called the function recursively swapping the destiny for origin and the isDigraph for 1 to don't repeat again
  if(isDigraph == 0) {
    insertingEdges(newGraph, destiny, origin, 1, weight);
  }

  return 1;
}

//Function that will remove edges in the graph
int removingEdges(Graph * newGraph, int origin, int destiny, int isDigraph) {
  //Verifying if the parameters are right
  if(newGraph == NULL) {
    return 0;
  }
  if(origin < 0 || origin >= newGraph->numOfVertices) {
    return 0;
  }
  if(destiny < 0 || destiny >= newGraph->numOfVertices) {
    return 0;
  }

  int i = 0;
  //Trying to find the index of the matrix that is equal destiny
  while(i < newGraph->grade[destiny] && newGraph->edges[origin][i] != 1)

  //If the while broke, and i is equal to newGraph->grade[origin], this mean that the destiny was not find  and return 0
  if(i == newGraph->grade[origin]) {
    return 0;
  }

  //Decreasing the aumont of index in grade
  newGraph->grade[origin]--;

  //Setting that the edge with "i" position is equal to the last item of the edge 
  newGraph->edges[origin][i] = newGraph->edges[origin][newGraph->grade[destiny]];

  //If the graph is weighted, if it is, set the edge with "i" position equal to the last item of the edge
  if(newGraph->isWeighted) {
    newGraph->weights[origin][i] = newGraph->edges[origin][newGraph->grade[destiny]];
  }

  //If the graph is digraph, it is called recursively the function swapping the destiny for origin and isDigraph equal to 1 that will stop the recusive calls
  if(isDigraph) {
    removingEdges(newGraph, destiny, origin, 1);
  }

  return 1;
}

//Function that will free the structure memory
void freeGraph(Graph *newGraph) {
  if(newGraph != NULL) {
    
    //For used to free the line of each edge
    for(int i = 0; i < newGraph->numOfVertices; i++) {
      free(newGraph->edges[i]);
    }
    //Free all edges
    free(newGraph->edges);

    //Verifying if the graph is weighted
    if(newGraph->isWeighted) {
      //For used to free the line of each weighted edge
      for(int i = 0; i < newGraph->numOfVertices; i++) {
        free(newGraph->weights[i]);
      }
      //Free all weighted edges
      free(newGraph->weights);
    }
    
    //Free the grade of the graph
    free(newGraph->grade);

    //Free the graph
    free(newGraph);
  }
}

//Function that will print the whole graph
void showGraphAdjacent(Graph *newGraph) {
  printf("Matriz adjacente: \n[\n");
  for(int i = 0; i < newGraph->numOfVertices; i++) {
    for(int j = 0; j < newGraph->maxGrade; j++) {
      printf(" %d ", newGraph->edges[i][j]);
    }
    printf("\n");
  }
  printf("]\n");
}

int main(void) {
  Graph *newGraph;

  newGraph = createNewGraph(3, 3, 0);
  insertingEdges(newGraph, 0, 1, 0, 0);
  insertingEdges(newGraph, 2, 1, 0, 0);
  insertingEdges(newGraph, 1, 1, 0, 0);

  removingEdges(newGraph, 1, 1, 0);


  showGraphAdjacent(newGraph);

  freeGraph(newGraph);
  return 0;
}
//Definindo os protótipos do programa

typedef struct graph Graph;

//Function that will struture a new graph with values
Graph *createNewGraph(int numOfVertices, int maxGrade, int isWeighted);

//We can call this function like this...
//Graph *myGraph;
//myGraph = createNewGraph(10, 7, 0);

//Function that will free the struct memory
void freeGraph(Graph *newGraph);

//Function that will insert new edges in the graph
int insertingEdges(Graph *newGraph, int origin, int destiny, int isDigraph, float weight);

//Function that will remove edges in the graph
int removingEdges(Graph *newGraph, int origin, int destiny, int isDigraph);

//Function that will print the whole graph
void showGraphAdjacent(Graph *newGraph);
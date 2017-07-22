// Program to find negative cycle in bellman ford
#include <stdio.h>
#include <limits>
#include <string>
#include <math.h>

using namespace std;

struct Vertex
{
  int id;
  string name;
};

struct Edge
{
  int fromId;
  int toId;
  double cost;
};

struct Graph
{
  Vertex *vertices;
  Edge *edges;
};

void SetVertex(Vertex* vertex, int id, string name)
{
  vertex->id = id;
  vertex->name = name;
}

void SetEdge(Edge* edge, int sourceId, int destinationId, double cost)
{
  edge->fromId = sourceId;
  edge->toId = destinationId;
  edge->cost = cost;
}

double NegativeLogRate(double rate)
{
  return -log(rate);
}

Graph* GetInputGraphProfit(int &numberOfVertices, int &numberOfEdges)
{
  numberOfVertices = 6;
  numberOfEdges = 6;

  Graph *graph = new Graph;
  graph->vertices = new Vertex[numberOfVertices];
  graph->edges = new Edge[numberOfEdges];

  SetVertex(&graph->vertices[0], 0, "USD");
  SetVertex(&graph->vertices[1], 1, "SGD");
  SetVertex(&graph->vertices[2], 0, "MYR");
  SetVertex(&graph->vertices[3], 0, "INR");
  SetVertex(&graph->vertices[4], 0, "GBP");
  SetVertex(&graph->vertices[5], 0, "CAD");

  SetEdge(&graph->edges[0], 0, 1, NegativeLogRate(1.38));
  SetEdge(&graph->edges[1], 1, 2, NegativeLogRate(3.08));
  SetEdge(&graph->edges[2], 2, 3, NegativeLogRate(15.12));
  SetEdge(&graph->edges[3], 3, 4, NegativeLogRate(0.012));
  SetEdge(&graph->edges[4], 4, 0, NegativeLogRate(1.30));
  SetEdge(&graph->edges[5], 5, 4, NegativeLogRate(1.30));
  
  return graph;
}

Graph* GetInputGraphLoss(int &numberOfVertices, int &numberOfEdges)
{
  numberOfVertices = 5;
  numberOfEdges = 5;
  
  Graph *graph = new Graph;
  graph->vertices = new Vertex[numberOfVertices];
  graph->edges = new Edge[numberOfEdges];

  SetVertex(&graph->vertices[0], 0, "USD");
  SetVertex(&graph->vertices[1], 1, "SGD");
  SetVertex(&graph->vertices[2], 0, "MYR");
  SetVertex(&graph->vertices[3], 0, "INR");
  SetVertex(&graph->vertices[4], 0, "GBP");
	
  SetEdge(&graph->edges[0], 0, 1, NegativeLogRate(1.38295));
  SetEdge(&graph->edges[1], 1, 2, NegativeLogRate(3.08614));
  SetEdge(&graph->edges[2], 2, 3, NegativeLogRate(15.0996));
  SetEdge(&graph->edges[3], 3, 4, NegativeLogRate(0.0119755));
  SetEdge(&graph->edges[4], 4, 0, NegativeLogRate(1.295));
	
  return graph;
}

void InitializeDistance(double *distance, int numberOfVertices)
{
  for(int i=0; i<numberOfVertices; i++)
    distance[i] = numeric_limits<double>::max();
}

void InitializePredecessor(int *predecessor, int numberOfVertices)
{
  for(int i=0; i<numberOfVertices; i++)
    predecessor[i] = -1;
}

bool Relax (Edge *e, double* distance, int* predecessor)
{
  if(distance[e->fromId] != numeric_limits<double>::max() && distance[e->toId] > distance[e->fromId] + e->cost)
  {
    distance[e->toId] = distance[e->fromId] + e->cost;
    predecessor[e->toId] = e->fromId;
    return true;
  }

  return false;
}

bool BellmanFord(Graph *graph, int numberOfVertices, int numberOfEdges, int source, double* distance, int* predecessor, int &edgeWithNegativeCycle)
{
  distance[source] = 0;

  bool valueChanged;
  for(int i=0; i<numberOfVertices-1; i++)
  {
    valueChanged = false;
    for(int j=0; j<numberOfEdges; j++)
      valueChanged = valueChanged || Relax(&graph->edges[j], distance, predecessor);

    if(!valueChanged)
      return true;
  }

  for(int j=0; j<numberOfEdges; j++)
    if(Relax(&graph->edges[j], distance, predecessor))
    {
      edgeWithNegativeCycle = j;
      return false;
    }
}

void PrintCycle(Graph* graph, int *predecessor, int currentVertex, int firstVertex)
{
  currentVertex = predecessor[currentVertex];
  if(currentVertex == firstVertex)
    return;
		
  PrintCycle(graph, predecessor, currentVertex, firstVertex);
  printf("-> %s ", graph->vertices[currentVertex].name.c_str());
}

void Call(Graph *graph, int numberOfVertices, int numberOfEdges)
{
  double *distance = new double[numberOfVertices];
  int *predecessor = new int[numberOfVertices];

  InitializeDistance(distance, numberOfVertices);
  InitializePredecessor(predecessor, numberOfVertices);

  int edgeWithNegativeCycle;
  bool success = BellmanFord(graph, numberOfVertices, numberOfEdges, 0, distance, predecessor, edgeWithNegativeCycle);

  if(!success)
  {
    printf("Profit making cycle: %s", graph->vertices[graph->edges[edgeWithNegativeCycle].fromId].name.c_str());
    PrintCycle(graph, predecessor, graph->edges[edgeWithNegativeCycle].fromId, graph->edges[edgeWithNegativeCycle].fromId);
    printf("\n\n");
  }
  else
    printf("No luck here\n\n");
}

int main()
{
  int numberOfVertices, numberOfEdges;

  Graph* graph = GetInputGraphProfit(numberOfVertices, numberOfEdges);
  Call(graph, numberOfVertices, numberOfEdges);

  graph = GetInputGraphLoss(numberOfVertices, numberOfEdges);
  Call(graph, numberOfVertices, numberOfEdges);
}

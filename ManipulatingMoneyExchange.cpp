//JLTi Code Jam Jun 2017
//https://gopalcdas.wordpress.com/2017/06/08/manipulating-money-exchange/
#include <stdio.h>
#include <limits>
#include <string>
#include <math.h>

using namespace std;

#define EXTRA_CURRENCY "NOC"

struct Vertex
{
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

void SetVertex(Vertex* vertex, string name)
{
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
  numberOfVertices = 7;
  numberOfEdges = 12;

  Graph *graph = new Graph;
  graph->vertices = new Vertex[numberOfVertices];
  graph->edges = new Edge[numberOfEdges];

  SetVertex(&graph->vertices[0], EXTRA_CURRENCY);
  SetVertex(&graph->vertices[1], "USD");
  SetVertex(&graph->vertices[2], "SGD");
  SetVertex(&graph->vertices[3], "MYR");
  SetVertex(&graph->vertices[4], "INR");
  SetVertex(&graph->vertices[5], "GBP");
  SetVertex(&graph->vertices[6], "CAD");

  SetEdge(&graph->edges[0], 0, 1, 0);
  SetEdge(&graph->edges[1], 0, 2, 0);
  SetEdge(&graph->edges[2], 0, 3, 0);
  SetEdge(&graph->edges[3], 0, 4, 0);
  SetEdge(&graph->edges[4], 0, 5, 0);
  SetEdge(&graph->edges[5], 0, 6, 0);

  SetEdge(&graph->edges[6], 1, 2, NegativeLogRate(1.38));
  SetEdge(&graph->edges[7], 2, 3, NegativeLogRate(3.08));
  SetEdge(&graph->edges[8], 3, 4, NegativeLogRate(15.12));
  SetEdge(&graph->edges[9], 4, 5, NegativeLogRate(0.012));
  SetEdge(&graph->edges[10], 5, 1, NegativeLogRate(1.30));
  SetEdge(&graph->edges[11], 6, 5, NegativeLogRate(1.30));

  return graph;
}

Graph* GetInputGraphLoss(int &numberOfVertices, int &numberOfEdges)
{
  numberOfVertices = 6;
  numberOfEdges = 10;

  Graph *graph = new Graph;
  graph->vertices = new Vertex[numberOfVertices];
  graph->edges = new Edge[numberOfEdges];

  SetVertex(&graph->vertices[0], EXTRA_CURRENCY);
  SetVertex(&graph->vertices[1], "USD");
  SetVertex(&graph->vertices[2], "SGD");
  SetVertex(&graph->vertices[3], "MYR");
  SetVertex(&graph->vertices[4], "INR");
  SetVertex(&graph->vertices[5], "GBP");
	
  SetEdge(&graph->edges[0], 0, 1, 0);
  SetEdge(&graph->edges[1], 0, 2, 0);
  SetEdge(&graph->edges[2], 0, 3, 0);
  SetEdge(&graph->edges[3], 0, 4, 0);
  SetEdge(&graph->edges[4], 0, 5, 0);

  SetEdge(&graph->edges[5], 1, 2, NegativeLogRate(1.38295));
  SetEdge(&graph->edges[6], 2, 3, NegativeLogRate(3.08614));
  SetEdge(&graph->edges[7], 3, 4, NegativeLogRate(15.0996));
  SetEdge(&graph->edges[8], 4, 5, NegativeLogRate(0.0119755));
  SetEdge(&graph->edges[9], 5, 1, NegativeLogRate(1.295));
	
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
      valueChanged = Relax(&graph->edges[j], distance, predecessor) || valueChanged;

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

void PrintNegativeResult(Graph *graph, int *predecessor, int edgeWithNegativeCycle)
{
  printf("Profit making cycle: %s", graph->vertices[graph->edges[edgeWithNegativeCycle].fromId].name.c_str());
  PrintCycle(graph, predecessor, graph->edges[edgeWithNegativeCycle].fromId, graph->edges[edgeWithNegativeCycle].fromId);
  printf("\n\n");
}

void PrintResult(Graph *graph, int *predecessor, bool success, int edgeWithNegativeCycle)
{
  if(!success)
    PrintNegativeResult(graph, predecessor, edgeWithNegativeCycle);
  else
    printf("No luck here\n\n");
}

void Call(Graph *graph, int numberOfVertices, int numberOfEdges)
{
  double *distance = new double[numberOfVertices];
  int *predecessor = new int[numberOfVertices];

  InitializeDistance(distance, numberOfVertices);
  InitializePredecessor(predecessor, numberOfVertices);

  int edgeWithNegativeCycle;
  bool success = BellmanFord(graph, numberOfVertices, numberOfEdges, 0, distance, predecessor, edgeWithNegativeCycle);

  PrintResult(graph, predecessor, success, edgeWithNegativeCycle);
}

int main()
{
  int numberOfVertices, numberOfEdges;

  Graph* graph = GetInputGraphProfit(numberOfVertices, numberOfEdges);
  Call(graph, numberOfVertices, numberOfEdges);

  graph = GetInputGraphLoss(numberOfVertices, numberOfEdges);
  Call(graph, numberOfVertices, numberOfEdges);
}

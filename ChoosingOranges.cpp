//JLTi Code Jam Oct 2017
//https://gopalcdas.wordpress.com/2017/10/14/choosing-oranges/

#include <stdio.h>
#include <queue>

using namespace std;

struct Node
{
  int score;
  int index;

  bool operator<(const Node& rhs) const
  {
    return score < rhs.score;
  }
};

Node *BuildNodes(int *scores, int n);
int *BestScores(int *scores, int n);
void FindBestScores(Node *nodes, int* scores1, int n, int m, int *bestScores);
void PrintScores(int *scores, int *bestScores, int n);

int main()
{
  int m = 5;
  int scores1[] = { 1, 3, 5, 7, 3, 5, 9, 1, 2, 5 };
  int n = sizeof(scores1) / sizeof(scores1[0]);	
  FindBestScores(BuildNodes(scores1, n), scores1, n, m, BestScores(scores1, n));

  m = 4;
  int scores2[] = { 1, 3, 5};
  n = sizeof(scores2) / sizeof(scores2[0]);
  FindBestScores(BuildNodes(scores2, n), scores2, n, m, BestScores(scores2, n));

  m = 3;
  int scores3[] = { 1, 2, 4, 9 };
  n = sizeof(scores3) / sizeof(scores3[0]);
  FindBestScores(BuildNodes(scores3, n), scores3, n, m, BestScores(scores3, n));

  m = 7;
  int scores4[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  n = sizeof(scores4) / sizeof(scores4[0]);
  FindBestScores(BuildNodes(scores4, n), scores4, n, m, BestScores(scores4, n));

  m = 7;
  int scores5[] = { 9, 8, 7, 10, 6, 5, 4, 3, 2, 1 };
  n = sizeof(scores5) / sizeof(scores5[0]);
  FindBestScores(BuildNodes(scores5, n), scores5, n, m, BestScores(scores5, n));

  m = 7;
  int scores6[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
  n = sizeof(scores6) / sizeof(scores6[0]);
  FindBestScores(BuildNodes(scores6, n), scores6, n, m, BestScores(scores6, n));
}

Node *BuildNodes(int *scores, int n)
{
  Node *nodes = new Node[n];
  for (int i = 0; i < n; i++)
  {
    nodes[i].score = scores[i];
    nodes[i].index = i;
  }

  return nodes;
}

int *BestScores(int *scores, int n)
{
  int *bestScores = new int[n];
  for (int i = 0; i < n; i++)
    bestScores[i] = 0;

  return bestScores;
}

void FindBestScores(Node *nodes, int* scores, int n, int m, int *bestScores)
{
  if (n < m)
  {
    printf("None\n\n");
    return;
  }		

  std::priority_queue <Node> q;
  for (int i = 0; i < m - 1; i++)
    q.push(nodes[i]);

  for (int i = m-1; i < n; i++)
  {
    Node node = q.top();
    if (node.score <= nodes[i].score)
    {
      q.pop();
      bestScores[i] = 1;
      q.push(nodes[i]);
      continue;
    }

    q.push(nodes[i]);
		
    while (node.index < (i + 1 - m))
    {
      q.pop();
      node = q.top();			
    }			

    bestScores[node.index] = 1;

    if (node.index == (i + 1 - m))
      q.pop();
  }

  PrintScores(scores, bestScores, n);
}

void PrintScores(int *scores, int *bestScores, int n)
{
  bool firstPrinted = false;
  for (int i = 0; i < n; i++)
    if (bestScores[i])
    {
      if(firstPrinted)
        printf(", %d", scores[i]);
      else
      {
        firstPrinted = true;
        printf("%d", scores[i]);
      }
    }
	
  printf("\n\n");
}

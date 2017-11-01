//JLTi Code Jam Sep 2017
//https://gopalcdas.wordpress.com/2017/10/14/choosing-oranges/

#include <stdio.h>
 
using namespace std;
 
int DaysRequired(int **adjMatrix, int n, int v);
bool TryWithDays(int **adjMatrix, int n, int m, int startColor, int v, int *chosenColors);
bool ThisColorWorks(int **adjMatrix, int v, int color, int *chosenColors);
int *ChosenColors(int n);
int **getAdjMatrix(int n);
 
int main()
{
  int n = 2;
  int **adjMatrix = getAdjMatrix(n);
  //1 2
  adjMatrix[0][1] = 1;
  adjMatrix[1][0] = 1;
  printf("%d\n", DaysRequired(adjMatrix, n, 1)); 
 
  n = 3;
  adjMatrix = getAdjMatrix(n);
  //1 2
  adjMatrix[0][1] = 1;
  adjMatrix[1][0] = 1;
  //2 3
  adjMatrix[1][2] = 1;
  adjMatrix[2][1] = 1;
  printf("%d\n", DaysRequired(adjMatrix, n, 1));
 
  n = 3;
  adjMatrix = getAdjMatrix(n);
  //1 2
  adjMatrix[0][1] = 1;
  adjMatrix[1][0] = 1;
  //2 3
  adjMatrix[1][2] = 1;
  adjMatrix[2][1] = 1;
  //1 3
  adjMatrix[0][2] = 1;
  adjMatrix[2][0] = 1;
  printf("%d\n", DaysRequired(adjMatrix, n, 1));
}
 
int **getAdjMatrix(int n)
{
  int **adjMatrix = new int*[n];
  for (int i = 0; i < n; i++)
    adjMatrix[i] = new int[n];
 
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      adjMatrix[i][j] = 0;
  }
 
  return adjMatrix;
}
 
int DaysRequired(int **adjMatrix, int n, int m)
{
  for (int i = 1; i <= n; i++)
  {
    if (TryWithDays(adjMatrix, n, i, 1, 0, ChosenColors(n)))
      return i;
  }
 
  return 0;
}
 
bool TryWithDays(int **adjMatrix, int n, int m, int startColor, int v, int *chosenColors)
{
  if (n == v)
    return true;
 
  for (int i = startColor; i <= m; i++)
  {
    if (ThisColorWorks(adjMatrix, v, i, chosenColors))
    {
      chosenColors[v] = i;
      return TryWithDays(adjMatrix, n, m, 1, v + 1, chosenColors);
    }                   
  }
 
  //back track
  if (v == 0)
    return false;

  return TryWithDays(adjMatrix, n, m, chosenColors[v-1] + 1, v - 1, chosenColors);
}
 
bool ThisColorWorks(int **adjMatrix, int v, int color, int *chosenColors)
{
  for (int i = 0; i < v; i++)
  {
    if (adjMatrix[i][v] && chosenColors[i] == color)
      return false;
  }
 
  return true;
}

int *ChosenColors(int n)
{
  int *chosenColors = new int[n];
 
  for (int i = 0; i < n; i++)
    chosenColors[i] = 0;
 
  return chosenColors;
}

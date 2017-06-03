//JLTi Code Jam Apr 2017
//https://gopalcdas.wordpress.com/2017/05/01/jlti-code-jam-april-2017/

#include <queue>  
#include <iostream>  
#include <list>
#include <time.h>
#include <algorithm>
#include <functional>

unsigned int max(unsigned int a, unsigned int b)
{
  if(a>b)
    return a;

  return b;
}

int nextChosenItemIndex(std::vector<unsigned int> intputData, unsigned int &capacity, std::vector<unsigned int> &solution, int discardedChosenIndex)
{
  if(solution.size() == 0)
    return 0;

  int startIndex = max(discardedChosenIndex + 1, solution.back() + 1);
  for(unsigned int i=startIndex; i<intputData.size(); i++)
    if(intputData[i] <= capacity)
      return i;

  return -1;
}

bool GetNext(std::vector<unsigned int> intputData, unsigned int &capacity, std::vector<unsigned int> &solution)
{
  unsigned int nextChosenIndex;
  int discardedChosenIndex = -1;
  
  while(1)
  {
    //take next index matching criteria
    nextChosenIndex = nextChosenItemIndex(intputData, capacity, solution, discardedChosenIndex);

    // if found, return
    if(nextChosenIndex != -1)
      break;

    if(solution.size() == 0)
      return false;

    //remove last selected one
    discardedChosenIndex = solution.back();
    solution.pop_back();

    capacity = capacity + intputData[discardedChosenIndex];
  }

  solution.push_back(nextChosenIndex);
  capacity = capacity - intputData[nextChosenIndex];

  return true;
}

std::vector<unsigned int> GetSolution(std::vector<unsigned int> intputData, unsigned int capacity, bool &success)
{
  success = true;
  std::vector<unsigned int> solution;

  while(success)
  {
    success = GetNext(intputData, capacity, solution);
    if(capacity == 0)
      break;
  }

  return solution;
}

std::vector<unsigned int> ClearUsedPeople(std::vector<unsigned int> intputData, std::vector<unsigned int> solution)
{
  std::vector<unsigned int>::iterator i = solution.end();
  
  while (i != solution.begin())
  {
    --i;
    intputData.erase(intputData.begin() + *i);
  }

  return intputData;
}

bool SanityCheckingSucceeded(std::vector<unsigned int> intputData, unsigned int capacity)
{
  if(capacity == 0)
    return false;

  unsigned int sum = 0;
  for(unsigned int i=0; i<intputData.size(); i++)
  {
    if(intputData[i] > capacity)
      return false;

    sum = sum + intputData[i];
  }

  return sum % capacity == 0;
}

std::vector<unsigned int> ConvertSolutionIndexToWeight(std::vector<unsigned int> solution, std::vector<unsigned int> intputData)
{
  std::vector<unsigned int> solutionInWeight;
  for(unsigned int i = 0; i<solution.size(); i++)
    solutionInWeight.push_back(intputData[solution[i]]);

  return solutionInWeight;
}

std::vector<std::vector<unsigned int>> Solve(std::vector<unsigned int> intputData, unsigned int capacity, bool &success)
{
  success = true;
  std::vector<std::vector<unsigned int>> allSolutions;

  if(!SanityCheckingSucceeded(intputData, capacity))
  {
    success = false;
    return allSolutions;
  }

  while(success)
  {
    if(intputData.size() == 0)
      break;

    std::vector<unsigned int> solution = GetSolution(intputData, capacity, success);
		
    std::vector<unsigned int> solutionInWeight = ConvertSolutionIndexToWeight(solution, intputData);
    allSolutions.push_back(solutionInWeight);

    intputData = ClearUsedPeople(intputData, solution);
  }

  return allSolutions;
}

void PrintResult(std::vector<std::vector<unsigned int>> result, bool success)
{
  if(!success)
  {
    std::cout << "No crossing, change itinerary." << std::endl; 
    return;
  }

  for(unsigned int i=0; i<result.size(); i++)
  {
    printf("{");

    for(unsigned int j=0; j<result[i].size(); j++)
    {
      printf("%d", result[i][j]);
      if(j != result[i].size()-1)
        printf(",");
    }

     printf("}\n");
  }
}

std::vector<unsigned int> GenerateData(unsigned int &capacity)
{
  //capacity = 20;
  //unsigned int w[] = {10, 8, 7, 5, 5, 5};

  capacity = 10;
  unsigned int w[] = {2, 1, 7, 3, 2, 5, 1, 6, 1, 3, 9, 4, 2, 1, 1, 1, 1, 1, 2, 1, 1, 5};
  
  std::sort(w, w + sizeof(w) / sizeof(unsigned int), std::greater<unsigned int>());
	
  //capacity = 125;
  //unsigned int w[] = {45, 25, 80, 100, 125};

  //capacity = 120;
  //unsigned int w[] = {40, 20, 80, 100, 120, 70};

  std::vector<unsigned int> inputData (w, w + sizeof(w) / sizeof(unsigned int) );

  return inputData;
}

int main( )  
{  
  std::vector<std::vector<unsigned int>> result;
  unsigned int capacity;
  bool success;
  std::vector<unsigned int> intputData = GenerateData(capacity);
	
  clock_t tStart = clock();
  result = Solve(intputData, capacity, success);
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  PrintResult(result, success);
}

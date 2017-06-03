// JLTi Code Jam Mar 2017
// https://gopalcdas.wordpress.com/2017/05/02/jlti-code-jam-march-2017/

#include <queue>
#include <iostream>
#include <list>
#include <time.h>

const int TOTAL_PEOPLE = 1000000;
const int TOTAL_TEAM = 10000;

struct Node
{
  int teamNumber;
  int count;

  bool operator<(const Node& rhs) const
  {
    return count < rhs.count;
  }
};

std::vector<int> Solve(std::vector<int> intputData, int &success)
{
  std::priority_queue <Node> q;
  success = 1;
  std::vector<int> outputData;
  std::vector<Node> heapItems(TOTAL_TEAM + 1);

  for (int i = 1; i <= TOTAL_TEAM; i++)
  {
    heapItems[i].teamNumber = i;
    heapItems[i].count = 0;
  }

  for (int i = 0; i < TOTAL_PEOPLE; i++)
    heapItems[intputData[i]].count++;

  for (int i = 1; i <= TOTAL_TEAM; i++)
    if(heapItems[i].count > 0)
      q.push(heapItems[i]);

  Node last = {-1, 0};
  while(!q.empty())
  {
    const Node n = q.top( );
    q.pop(); 

    if(q.empty() && n.count > 1)
    {
      success = 0;
      break;
    }

    if(last.count != 0)
      q.push(last);

    outputData.push_back(n.teamNumber);

    last = n;
    last.count--;
  }

  return outputData;
}

std::vector<int> GenerateData()
{
  std::vector<int> inputData;
  for (int i = 0; i < TOTAL_PEOPLE; i++)
    inputData.push_back(1 + rand()%TOTAL_TEAM);

  return inputData;
}

bool VerifyData(std::vector<int> outputData)
{
  for (int i = 1; i < TOTAL_PEOPLE; i++)
    if (outputData[i - 1] == outputData[i])
      return false;

  return true;
}

int main( )  
{  
  int success;
  std::vector<int> intputData = GenerateData();
	
  clock_t tStart = clock();
  std::vector<int> outputData = Solve(intputData, success);
  printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

  if(success == 1)
  {
    bool result = VerifyData(outputData);
    std::cout << "Result " << result << "." << std::endl; 
  }
  else
    std::cout << "Nopt possible to rearrrange " << std::endl; 
}

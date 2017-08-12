//JLTi Code Jam Jul 2017
//https://gopalcdas.wordpress.com/2017/07/15/scoring-weight-loss/

#include <stdio.h>
#include <limits>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

enum Position { SMALLER_THAN_ALL = 1, BIGGER_THAN_ALL = 2, IN_THE_MIDDLE = 3 };

int DPN2(double weight[], int n);

int SkylineNlogN(double weight[], int n);

Position FindPosition(double n, vector<vector<double>> allPromisingLists, int& insertAt);
int ToBeReplacedItemIndex(vector<vector<double>> allPromisingLists, int l, int r, double v);

void DealWithThisNumber(double n, vector<vector<double>>& allPromisingLists, int insertAt, Position p);

void AddAtBeginning(double n, vector<vector<double>>& allPromisingLists);
void AddInMiddle(double v, vector<vector<double>>& allPromisingLists, int insertAt);
void AddAtEnd(double v, vector <vector<double>>& allPromisingLists);
vector<double> CopyFromLongest(vector<double> longest);

void Call(double weight[], int n);
double* Negative(double weight[], int n);
unsigned int GetBest(vector<vector<double>> allPromisingLists);

bool IsGreaterThan(double f, double s);
bool IsGreaterThanEqual(double f, double s);

int main()
{
	double weight1[] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
	int n = sizeof(weight1)/sizeof(weight1[0]);	
	Call(weight1, n);

	double weight2[] = { 73, 72.9, 72.8, 72.8, 72.9, 72.7, 72.0, 71.6, 73, 72.5, 72.4, 71.3, 73.5, 74 };
	n = sizeof(weight2)/sizeof(weight2[0]);
	Call(Negative(weight2, n), n);

	double weight3[] = { 95, 94, 97, 89, 99, 100, 101, 102, 103, 104, 105, 100, 95, 90 };
	n = sizeof(weight3)/sizeof(weight3[0]);
	Call(Negative(weight3, n), n);

	double weight4[] = { 95, 96, 93, 101, 91, 90, 89, 88, 87, 86, 85, 90, 95, 100 };
	n = sizeof(weight4)/sizeof(weight4[0]);
	Call(weight4, n);

	double weight5[] = { 53, 53.1, 53.2, 53.4, 53.5, 53.6, 53.9, 54, 54.1, 54.2, 54.2, 54.7, 55.8, 56 };
	n = sizeof(weight5)/sizeof(weight5[0]);
	Call(Negative(weight5, n), n);
}

void Call(double weight[], int n)
{
	printf("Score: %d\n\n", DPN2(weight, n));
	printf("Score: %d\n\n", SkylineNlogN(weight, n));	
}

double* Negative(double weight[], int n)
{
	for(int i=0; i<n; i++)
		weight[i] = -weight[i];

	return weight;
}

int DPN2(double weight[], int n)
{
	int *score = new int[n];
	for(int i=0; i<n; i++)
		score[i] = 1;

	int maxScore = 0;

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<i; j++)
			if(IsGreaterThan(weight[i], weight[j]) && score[i] < (score[j] + 1))
				score[i] = score[j] + 1;
	
		if(score[i] > maxScore)
			maxScore = score[i];
	}

	return maxScore;
}

int SkylineNlogN(double weight[], int n)
{
	vector<vector<double>> allPromisingLists;
	vector<double> longest;
	int insertAt;

	for(int i=0; i<n; i++)
	{
		Position p = FindPosition(weight[i], allPromisingLists, insertAt);
		DealWithThisNumber(weight[i], allPromisingLists, insertAt, p);
	}

	return GetBest(allPromisingLists);
}

Position FindPosition(double v, vector <vector<double>> allPromisingLists, int& insertAt)
{
	if(allPromisingLists.empty())
		return SMALLER_THAN_ALL;

	if(IsGreaterThanEqual(allPromisingLists.front().back(), v))
			return SMALLER_THAN_ALL;

	if(IsGreaterThan(v, allPromisingLists.back().back()))
		return BIGGER_THAN_ALL;

	insertAt = ToBeReplacedItemIndex(allPromisingLists, 0, allPromisingLists.size(), v);
	return IN_THE_MIDDLE;
}

int ToBeReplacedItemIndex(vector<vector<double>> allPromisingLists, int l, int r, double v)
{
	while(l < r-1)
	{
		int m = l + (r-l)/2;
		if(IsGreaterThanEqual(allPromisingLists.at(m).back(), v))
			r = m;
		else
			l = m;
	}

	return r;
}

void DealWithThisNumber(double v, vector<vector<double>>& allPromisingLists, int insertAt, Position p)
{
	switch(p)
	{
		case SMALLER_THAN_ALL:
			AddAtBeginning(v, allPromisingLists);
			break;

		case BIGGER_THAN_ALL:
			AddAtEnd(v, allPromisingLists);
			break;

		case IN_THE_MIDDLE:
			AddInMiddle(v, allPromisingLists, insertAt);
			break;

		default:
			break;
	}
}

void AddAtBeginning(double v, vector <vector<double>>& allPromisingLists)
{
	if(allPromisingLists.size() == 0)
	{
		vector<double> smallest;
		smallest.push_back(v);

		allPromisingLists.push_back(smallest);
	}

	allPromisingLists.at(0).pop_back();
	allPromisingLists.at(0).push_back(v);
}

void AddAtEnd(double v, vector <vector<double>>& allPromisingLists)
{
	vector<double> largest = CopyFromLongest(allPromisingLists.back());
	largest.push_back(v);
	allPromisingLists.insert(allPromisingLists.end(), largest);	
}

vector<double> CopyFromLongest(vector<double> longest)
{
	vector<double> newLongest;
	for(unsigned int i=0; i<longest.size(); i++)
		newLongest.push_back(longest.at(i));
	
	return newLongest;
}

void AddInMiddle(double v, vector<vector<double>>& allPromisingLists, int insertAt)
{
	allPromisingLists.at(insertAt).pop_back();
	allPromisingLists.at(insertAt).push_back(v);
}

vector<double> CopyFromBiggestMatchingEnding(vector<vector<double>>& allPromisingLists, int copyFrom)
{
	vector<double> newSeq;
	for(unsigned int i=0; i<allPromisingLists.at(copyFrom).size(); i++)
		newSeq.push_back(allPromisingLists.at(copyFrom).at(i));
	
	return newSeq;
}

unsigned int GetBest(vector<vector<double>> allPromisingLists)
{
	unsigned int max = 0;
	for(unsigned int i=0; i<allPromisingLists.size(); i++)
		if(allPromisingLists.at(i).size() > max)
			max = allPromisingLists.at(i).size();

	return max;
}

bool IsGreaterThan(double f, double s)
{
	return (f - s) > std::numeric_limits<double>::epsilon();
}

bool IsGreaterThanEqual(double f, double s)
{
	return ((f - s) > std::numeric_limits<double>::epsilon()) || (std::fabs(f - s) < std::numeric_limits<double>::epsilon());
}

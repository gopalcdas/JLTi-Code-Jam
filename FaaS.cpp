//JLTi Code Jam Aug 2017
//https://gopalcdas.wordpress.com/2017/08/05/faas/

#include <stdio.h>
#include <limits>
#include <vector>

using namespace std;

#define DAILY_PRICE 6
#define WEEKLY_PRICE 27.99
#define MONTHLY_PRICE 99.99

#define DAYS_IN_WEEK 5
#define DAYS_IN_MONTH 20

double DP(int weight[], int n);

bool IsGreaterThan(double f, double s);
template <typename T> T Cheapest(T a, T b, T c);

int main()
{
  int lunchDays1[] = { 1, 2, 4, 5, 17, 18 };
  int n = sizeof(lunchDays1)/sizeof(lunchDays1[0]);
  printf("Best Price: %.2f\n\n", DP(lunchDays1, n));

  int lunchDays2[] = { 3, 4, 5, 6, 7, 17, 18 };
  n = sizeof(lunchDays2)/sizeof(lunchDays2[0]);
  printf("Best Price: %.2f\n\n", DP(lunchDays2, n));

  int lunchDays3[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 19, 20, 21, 24 };
  n = sizeof(lunchDays3)/sizeof(lunchDays3[0]);
  printf("Best Price: %.2f\n\n", DP(lunchDays3, n));
}

double DP(int lunchDays[], int n)
{
  int m = lunchDays[n-1] + 1;
  double *bestPrice = new double[m];

  int lastIndex = 0;
  for(int i=0; i<n; i++)
  {
    for(int j=lastIndex; j<lunchDays[i]; j++)
      bestPrice[j] = 0;

    bestPrice[lunchDays[i]] = 1;
    lastIndex = lunchDays[i]+1;
  }

  for(int i=1; i<m; i++)
  {
    if(IsGreaterThan(bestPrice[i], 0))
    {
      double dailyBasisPrice = bestPrice[i-1] + DAILY_PRICE;
      double weeklyBasisPrice = i-DAYS_IN_WEEK >=0 ? bestPrice[i-DAYS_IN_WEEK] + WEEKLY_PRICE : numeric_limits<double>::max();
      double monthlyBasisPrice = i-DAYS_IN_MONTH >=0 ? bestPrice[i-DAYS_IN_MONTH] + MONTHLY_PRICE : numeric_limits<double>::max();

      bestPrice[i] = Cheapest(dailyBasisPrice, weeklyBasisPrice, monthlyBasisPrice);
    }
    else
      bestPrice[i] = bestPrice[i-1];
  }

  return bestPrice[m-1];
}

template <typename T> T Cheapest(T a, T b, T c)
{
  T cheapest = min(a, b);
  return min(cheapest, c);
}

bool IsGreaterThan(double f, double s)
{
  return (f - s) > std::numeric_limits<double>::epsilon();
}

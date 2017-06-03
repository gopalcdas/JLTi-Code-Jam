// JLTi Code Jam Mar 2017
// https://gopalcdas.wordpress.com/2017/05/07/jlti-code-jam-may-2017/

#include <stdio.h>
#include <limits>  

double maxOutOfThree(double a, double b, double c)
{
  double max;
  max = a > b ? a : b;
  if(c > max)
    return c;

  return max;
}

double GetMax(double price[], int start, int end)
{
  double max = -1;
  for(int i=start; i<=end; i++)
    if(price[i] > max)
      max = price[i];

  return max;
}

double GetMin(double price[], int start, int end)
{
  double min = std::numeric_limits<double>::max();
  for(int i=start; i<=end; i++)
    if(price[i] < min)
      min = price[i];
  
  return min;
}

void StockN2(double price[], int n, double &maxProfit, int &buyDay, int &sellDay)
{
  for(int i=0; i<n; i++)
    for(int j=i+1; j<n-1; j++)
    {
      if(price[j] - price[i] > maxProfit)
      {
        maxProfit = price[j] - price[i];
	buyDay = i;
	sellDay = j;
      }
    }
}

void StockGreedyOptimizedN(double price[], int start, int end, double &maxProfit, double &minValue, double &maxValue)
{
  if(start == end)
  {
    // just one value, return
    maxProfit = 0;
    minValue = maxValue = price[end];
    return;
  }

  int mid = start + (end-start)/2;

  double leftMaxProfit, leftMinValue, leftMaxValue;
  StockGreedyOptimizedN(price, start, mid, leftMaxProfit, leftMinValue, leftMaxValue);

  double rightMaxProfit, rightMinValue, rightMaxValue;
  StockGreedyOptimizedN(price, mid + 1, end, rightMaxProfit, rightMinValue, rightMaxValue);

  maxProfit = maxOutOfThree(leftMaxProfit, rightMaxProfit, rightMaxValue - leftMinValue);

  minValue = leftMinValue > rightMinValue ? rightMinValue : leftMinValue;
  maxValue = leftMaxValue > rightMaxValue ? leftMaxValue : rightMaxValue;
}

void StockGreedyNlogN(double price[], int start, int end, double &maxProfit)
{
  if(start == end)
  {
    // just one value, return
    maxProfit = 0;
    return;
  }

  int mid = start + (end-start)/2;

  double leftMaxProfit;
  StockGreedyNlogN(price, start, mid, leftMaxProfit);

  double rightMaxProfit;
  StockGreedyNlogN(price, mid+1, end, rightMaxProfit);

  double minLeft = GetMin(price, start, end);
  double maxRight = GetMax(price, start, end);

  double minValue = GetMin(price, start, mid);
  double maxValue = GetMax(price, mid+1, end);
  maxProfit = maxOutOfThree(leftMaxProfit, rightMaxProfit, maxValue - minValue);
}

int main()
{
  double price[] = { 2, 10, 5, 12, 1, 3, 11, 9 };
  int n = sizeof(price)/sizeof(price[0]);

  double maxProfit = -1;
  int buyDay, sellDay, i, j;
  StockN2(price, n, maxProfit, buyDay, sellDay);

  if(maxProfit > 0)
    printf("Buy on %d at %f, Sell on %d at %f, Make $: %f\n\n", buyDay + 1, price[buyDay], sellDay + 1, price[sellDay], maxProfit);
  else
    printf("Don't buy stock!\n\n");

  maxProfit = -1;
  StockGreedyNlogN(price, 0, n-1, maxProfit);

  if(maxProfit > 0)
    printf("Make $: %f\n\n", maxProfit);
  else
    printf("Don't buy stock!\n\n");

  maxProfit = -1;
  double minValue = std::numeric_limits<double>::max(), maxValue = 0;
  StockGreedyOptimizedN(price, 0, n-1, maxProfit, minValue, maxValue);
  if(maxProfit > 0)
    printf("Make $: %f\n\n", maxProfit);
  else
    printf("Don't buy stock!\n\n");
}

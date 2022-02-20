#include <sys/time.h>

#include <iostream>
#include <set>

using namespace std;

#define X 1000000

int main()
{
  set<int> setNum;

  int test = 0;
  double time_use;
  struct timeval start;
  struct timeval end;
  gettimeofday(&start, NULL);
  for (int i = 0; i < X; i++)
  {
    if (setNum.empty() == false)
    {
      for (int j : setNum)
      {
        test++;
      }
    }
  }
  gettimeofday(&end, NULL);
  time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
  cout << "empty:" << time_use / 1000 << "ms" << endl;

  gettimeofday(&start, NULL);
  for (int i = 0; i < X; i++)
  {
    for (int j : setNum)
    {
      test++;
    }
  }
  gettimeofday(&end, NULL);
  time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
  cout << "no_empty,foreach:" << time_use / 1000 << "ms" << endl;

  gettimeofday(&start, NULL);
  for (int i = 0; i < X; i++)
  {
    for (auto it = setNum.begin(); it != setNum.end(); it++)
    {
      test++;
    }
  }
  gettimeofday(&end, NULL);
  time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
  cout << "no_empty,iterator:" << time_use / 1000 << "ms" << endl;

  return 0;
}
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Solution
{
public:
  bool lemonadeChange(vector<int> &bills)
  {
    int fiveCount = 0;
    int tenCount = 0;

    for (int it : bills)
    {
      if (it == 5)
        fiveCount += 1;
      else if (it == 10)
      {
        // we need to return a 5, so we check if a 5 exists
        fiveCount -= 1;
        tenCount += 1;
      }
      else if (tenCount > 0)
      {
        // we need to give back 20 - 5 = $15
        fiveCount -= 1;
        tenCount -= 1;
      }
      else
      {
        fiveCount -= 3;
      }
      if (fiveCount < 0)
        return false;
    }
    return true;
  }
};

int main(int argc, char const *argv[])
{
  Solution sol;
  vector<int> bills = {5, 5, 5, 10, 20};
  cout << sol.lemonadeChange(bills) << endl;
  return 0;
}

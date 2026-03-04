#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int countOdds(int low, int high) {
    int hhigh = high;
    if (high & 1) { // subtract 1 from high
      high -= 1;
    }
    int range = high - low;
    int temp = ((range + 2 - 1) / 2);

    if (hhigh & 1) { // subtract 1 from high
      return temp += 1;
    } else {
      return temp;
    }
  }
};

int main(int argc, char *argv[]) {
  unsigned int low = 3, high = 7;
  Solution sol;
  cout << sol.countOdds(low, high) << endl;

  return 0;
}

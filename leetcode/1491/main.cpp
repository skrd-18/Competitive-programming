#include <algorithm>
#include <iostream>
#include <numeric>
#include <variant>
#include <vector>

using namespace std;

class Solution {
public:
  double average(vector<int> &salary) {
    // 1. Find the min and max elements
    auto min_it = std::min_element(salary.begin(), salary.end());
    salary.erase(min_it);
    auto max_it = std::max_element(salary.begin(), salary.end());
    salary.erase(max_it);

    double sum = accumulate(salary.begin(), salary.end(), 0.0);
    double average = sum / salary.size();

    return average;
  }
};

int main(int argc, char const *argv[]) {
  // Constraints are 3 <= salary.length <= 100
  // Returns a pair of iterators to the min and max elements
  Solution sol;
  vector<int> salary = {1000, 9000, 2000, 3000, 4000, 6000};
  double answer = sol.average(salary);
  cout << "answer: " << answer << endl;

  return 0;
}

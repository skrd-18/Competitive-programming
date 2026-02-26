#include <climits>
#include <iostream>
#include <vector>

class Solution {
public:
  bool canMakeArithmeticProgression(std::vector<int> &arr) {
    if (arr.size() <= 2)
      return true;
    int min = INT_MAX, max = (-2147483647 - 1);
    for (int num : arr) {
      min = std::min(min, num);
      max = std::max(max, num);
    }
    if ((max - min) % (arr.size() - 1) != 0)
      return false;
    int d = (max - min) / (arr.size() - 1);

    int i = 0;
    std::cout << "min = " << min << std::endl;
    while (i < arr.size()) {
      if (arr[i] == min + i * d)
        i++;
      else if ((arr[i] - min) % d != 0)
        return false;
      else {
        int pos = (arr[i] - min) / d;
        if (pos < i || arr[pos] == arr[i])
          return false;
        std::swap(arr[i], arr[pos]);
      }
    }
    return true;
  }
};

int main(int argc, char *argv[]) {

  Solution sol;
  std::vector<int> arr = {3, 5, 1};
  bool result = sol.canMakeArithmeticProgression(arr);
  std::cout << result << std::endl;

  return 0;
}

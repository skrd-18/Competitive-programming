#include <iostream>
#include <unordered_map>

using namespace std;

int romanToInt(string s);

int main() {
  string s = "LVIII";
  cout << romanToInt(s);
  return 0;
}

int romanToInt(string s) {
  unordered_map<char, int> T = {{'I', 1},   {'V', 5},   {'X', 10},  {'L', 50},
                                {'C', 100}, {'D', 500}, {'M', 1000}};
  int sum = T[s.back()]; // get the last element
  for (int i = s.length() - 2; i >= 0; --i) {
    cout << i << endl;
    if (T[s[i]] < T[s[i + 1]]) {
      sum -= T[s[i]];
    } else {
      sum += T[s[i]];
    }
  }
  return sum;
}

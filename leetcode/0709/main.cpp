#include <cstring>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

class Solution {
public:
  string toLowerCase(string s) {
    char a[s.length() + 1]; // account for the NULL terminated character
    strcpy(a, s.c_str());

    cout << "char array: " << a << endl;

    for (int i = 0; i < sizeof(a); i++)
      if ('A' <= a[i] && a[i] <= 'Z')
        a[i] = (char)(a[i] - 'A' + 'a');

    // Convert the char array back to string
    string res(a);

    return a;
  }
};

int main(int argc, char *argv[]) {

  Solution sol;
  cout << "answer: " << sol.toLowerCase("LoveLY") << endl;

  return 0;
}

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
    int n = 0;
    long long temp = 0;
    cin >> n;

    vector<long long int> nums;
    for (long long int i = 0; i < n; i += 1)
    {
        cin >> temp;
        nums.push_back(temp);
    }
    // returns a pair of iterators {min, max}
    auto result = minmax_element(nums.begin(), nums.end());

    cout << *result.second << " " << *result.first;
    return 0;
}
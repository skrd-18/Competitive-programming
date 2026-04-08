#include <iostream>
#include <vector>
#include <sys/types.h>
#include <string>
#include <algorithm> // For std::min
#include <utility>
#include <cmath>
#include <climits> // For LLONG_MAX
#include <iterator>
using namespace std;

int main(int argc, char const *argv[])
{
    long long total_hours = 0;
    long N = 0;

    if (!(std::cin >> N))
        return 0; // Read the '10'

    std::vector<int> nums(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> nums[i]; // Read each of the following 10 numbers
    }

    long long smallest = LLONG_MAX;
    for (int i = N - 1; i >= 0; i -= 1)
    {
        if (nums[i] < smallest)
        {
            smallest = nums[i];
        }
        total_hours += smallest;
    }

    cout << total_hours << endl;
    return 0;
}
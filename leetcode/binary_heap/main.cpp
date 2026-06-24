#include <iostream>
#include <vector>
#include <sys/types.h>
#include <string>
#include <algorithm> // For std::min
#include <utility>
#include <cmath>
#include <climits> // For LLONG_MAX
#include <iterator>
#include <queue>
using namespace std;

int main(int argc, char const *argv[])
{
    const auto data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};

    std::priority_queue<int> max_priority_queue;

    // Fill the priority queue.
    for (int n : data)
        max_priority_queue.push(n);

    cout << max_priority_queue.top() << endl;

    return 0;
}

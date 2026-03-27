#include <iostream>
#include <vector>
#include <sys/types.h>

using namespace std;

int main(int argc, char const *argv[])
{
    // how many units of m * s_i can fit into k

    // collect the input
    int n, m, k = 0;

    cin >> n >> m >> k;
    vector<int> array;
    long long days = 0;
    long long total = 0;
    long long rate = k / m; // integer division
    long long total_typos = 0;

    // Impossible condition
    if (m > k)
    {
        cout << ":(" << endl;
        return 0;
    }

    for (int i = 0; i < n; i += 1)
    {
        cin >> total;
        total_typos += total;
    }

    days += total_typos / rate;

    if (total_typos % rate != 0)
    {
        days += 1;
    }
    cout << days << endl;

    return 0;
}

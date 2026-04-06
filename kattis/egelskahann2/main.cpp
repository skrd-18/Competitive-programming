#include <iostream>
#include <vector>
#include <sys/types.h>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;

int main(int argc, char const *argv[])
{
    unsigned long long N = 0;
    cin >> N;
    // cout << "N " << N << endl;
    unsigned long long P = 1;
    unsigned long long L = 0;

    while (P * 2 <= N)
    {
        P *= 2;
    }
    // cout << "P " << P << endl;
    L = N - P;
    cout << (2 * L) + 1 << endl;
    return 0;
}
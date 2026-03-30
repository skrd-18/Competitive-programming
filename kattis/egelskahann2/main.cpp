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
    cout << "N " << N << endl;
    unsigned long long P = 0;
    unsigned long long k = 1;
    while (P < N)
    {
        P = pow(2, k);
        k += 1;
    }
    cout << "k " << k << endl;
    P = pow(2, k);
    cout << "P " << P << endl;
    return 0;
}
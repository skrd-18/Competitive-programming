#include <iostream>
using namespace std;
int main()
{
    int n, m; // n = number of goals scored and m = 0 or 1 or 2
    std::cin >> n >> m;
    if ((n == 0 && m == 0) || (n == 2 && m == 2))
    {
        cout << "Jebb" << endl;
    }
    else
    {
        cout << "Neibb" << endl;
    }
    return 0;
}
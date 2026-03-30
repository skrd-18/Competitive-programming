#include <iostream>
#include <vector>
#include <sys/types.h>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char const *argv[])
{
    int N = 0;
    cin >> N;
    string line;
    cin >> line;
    int a_win = 0;
    int h_win = 0;

    int a_count = 0;
    int h_count = 0;

    for (int i = 0; i < line.size(); i += 1)
    {
        // Check if a match is won
        if (a_count == 3)
        {
            a_win += 1;
            cout << "a_win " << a_win << endl;
            a_count = 0;
            h_count = 0;
        }

        if (h_count == 3)
        {
            h_win += 1;
            cout << "h_win " << h_win << endl;
            h_count = 0;
            a_count = 0;
        }

        // Check if a round is won
        if (a_win == N)
        {
            cout << "Hannes" << endl;
            return 0;
        }
        else if (h_win == N)
        {

            cout << "Arnar" << endl;
            return 0;
        }

        // Read a character and add a win.
        if (line[i] == 'A')
        {
            a_count += 1;
        }
        else if (line[i] == 'H')
        {
            h_count += 1;
        }

        cout << "Char " << line[i] << endl;
    }
    if (a_count == 3)
    {
        a_win += 1;
        cout << "a_win " << a_win << endl;
        a_count = 0;
        h_count = 0;
    }

    if (h_count == 3)
    {
        h_win += 1;
        cout << "h_win " << h_win << endl;
        h_count = 0;
        a_count = 0;
    }
    if (a_win == N)
    {
        cout << "Hannes" << endl;
        return 0;
    }
    else if (h_win == N)
    {

        cout << "Arnar" << endl;
        return 0;
    }

    return 0;
}
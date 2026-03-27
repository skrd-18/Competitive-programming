#include <iostream>
#include <vector>
#include <sys/types.h>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string res = "";
    string words;

    getline(cin, words);

    char last_printed = '\0';

    for (int i = 0; i < words.length(); i += 1)
    {
        if (words[i] != last_printed)
        {
            res.push_back(words[i]);
        }
        last_printed = words[i];
    }

    for (char c : res)
    {
        cout << c;
    }

    return 0;
}

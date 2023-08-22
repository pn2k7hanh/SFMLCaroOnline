#include <SFML/Network.hpp>

#include <iostream>
#include <Windows.h>


using namespace std;
using namespace sf;

int main()
{
    for (int i = 0; i < 3; cout << "step" << endl,i++)
    {
        cout << "inside" << endl;
    }

    return 0;
}
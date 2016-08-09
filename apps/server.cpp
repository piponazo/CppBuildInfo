#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
    cout << "Hello world: Server!" << endl;
    cout << "N Args: " << argc << endl;
    for (int i=0; i<argc; i++)
    {
        cout << "Args: " << argv[i] << endl;
    }
}

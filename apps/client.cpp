#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
    cout << "Hello world: Client!" << endl;
    cout << "N Args: " << argc << endl;
    cout << "Args: " << argv << endl;

    // The idea for the client application would be the following (idea taken from GNU time command):
    // - Parse the command line
    // - Start the measure
    // - Run command (Use QProcess with the objective to be platform independent)
    // - Stop the measure
}

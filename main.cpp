#include <iostream>
#include <luna/luna.h>

using namespace std;
using namespace luna;

int main()
{
    server s{server::port{7000}};
    cout << "Hello, World!" << endl;
    return 0;
}

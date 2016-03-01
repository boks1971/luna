#include <iostream>
#include <luna/luna.h>

using namespace std;
using namespace luna;

int main()
{
    server s{server::port{7000}, server::logger_cb{[](const std::string& mesg)
    {
        std::cout << mesg << std::endl;
    }}};


    s.handle_request(request_method::GET, "/hello", [](auto matches, auto params) -> response
    {
       return {"<h1>Hello, world!</h1>"};
    });

    while(s);
}

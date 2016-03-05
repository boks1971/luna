#include <iostream>
#include <luna/luna.h>

using namespace std;
using namespace luna;

int main()
{

    luna::set_logger([](luna::log_level level, const std::string& mesg)
    {
        std::cout << to_string(level) << ": " << mesg << std::endl;
    });


    server s{server::port{7000}};

    s.handle_request(request_method::GET, "/hello", [](auto matches, auto params) -> response
    {
       return {"<h1>Hello, world!</h1>"};
    });

    while(s);
}

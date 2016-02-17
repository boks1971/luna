---
layout: default
title: Luna
---

# A C++ library for embedding a webserver into your app

You are writing in C++ (because C++ is _awesome_), and your app needs to ac as an HTTP server. `libmicrohttpd` is super-awesome—except for that idiomatically C API. Luna is an idiomatically C++ wrapper for `libmicrohttpd`.

## Prerequisites

A C++11 compiler, cmake 3.3, libmicrohttpd.

## Example code

Here is some code for serving a simple JSON snippet from a single endpoint.

    #include <string>
    #include <luna/server.h>

    using namespace luna;

    int main(void)
    {
        server server{server::mime_type{"text/json"}, server::port{8443}};

        server.handle_response(request_method::GET, "/endpoint", [](std::vector<std::string> matches, query_params params, response &response) -> status_code
        {
            response = {"{\"made_it\": true}"};
            return 200;
        });

        while (server); //idle while the server is running. Totally not the best way. But this is demo code!
    }

## License

Apache License, Version 2.0

## Disclaimer

This library has only begun, and is a contant state of flux.
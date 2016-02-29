---
layout: default
title: Luna
---

# Luna

## An embedded HTTP server in C++14

You are writing in C++ (because C++ is _awesome_), and your app needs to act as an HTTP server. `libmicrohttpd` is super-awesome—except for that idiomatically C API. Luna is an idiomatically C++ wrapper for `libmicrohttpd`.

Luna is designed to be easy to use. HTTPD server creation, starting, shutting down, and deletion are all handled behind the scenes. Starting a server is automatic with server creation, and allowing a server object to fall out of scope is all that is needed to cleanly shut it down. There is nothing else for you to keep track of, or allocate.

## Prerequisites

A C++14 compiler (gcc 4.9, clang 3.3), cmake 3.2, libmicrohttpd.

## Example code

Here is some code for serving a simple JSON snippet from a single endpoint.

    #include <string>
    #include <luna/server.h>

    using namespace luna;

    int main(void)
    {
        server server{server::mime_type{"text/json"}, server::port{8443}};

        server.handle_response(request_method::GET,
                               "/endpoint",
                               [](auto matches, auto params)
                                   -> response
        {
            return {"{\"made_it\": true}"};
        });

        //idle while the server is running.
        //Totally not the best way.
        //But this is demo code!
        while (server);
    }

## License

Apache License, Version 2.0

## Disclaimer

This library has only begun, and is a contant state of flux.
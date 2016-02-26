---
layout: default
title: Serving a simple API endpoint
---

# HTTP Endpoint Basics

## Serving static HTML to a simple endpoint

(The code discussed here is available in `examples/example1.cpp`.)

Suppose we want to handle a request to `/hello_world` by responding with a simple HTML snippet:
    
    <h1>Hello, World!</h1>

Let's begin by writing a simple function to act as a request handler (nevermind what the request _is_).
    
    using namespace luna;
    response hello_world(const endpoint_matches &matches, 
                         const query_params     &params)
    {
        return {"<h1>Hello, World!</h1>"};
    }

Don't worry about the parameters to the function for now, since we are returning the HTML snippet unconditionally. The important bit is the return statement, which constructs a new `luna::response` object. This object actually has three components to it: An HTTP status code, a MIME type, and a string that contains the response body itself. The status code defaults to the appropriate success code for the HTTP method (201 for POST, 200 for everything else). The MIME type defaults to `"text/html"`. So we need only provide the HTML itself.

Now, let's create a `luna::server` to host this request handler, and attach the request handler to the server. We want our server to run on port 8443, and our request handler to trigger on a GET to `/hello_world`.

    int main(void)
    {
        server server{server::port{8443}};

        server.handle_request(request_method::GET,
                              "/hello_world",
                              &hello_world);

        while (server);
    }

The first line simply instantiates an HTTP server object on port 8443. The final line just loops forever. It is the second line that is of interest. This line instructs our server to listen for GET requests on `/hello_world`, and to call our request handler when it hears such a request.

## Using query parameters

(The code discussed here is available in `examples/example2.cpp`.)

Of course, we could have loaded this HTML from a file, rather than specifying it with a string constant. Or we can generate it dynamically based on the HTTP query parameters. Indeed, let's modify our example to echo back the query parameters received.

`luna::query_params` is simply an alias for a key-value hash stored as an `std::map`. The keys and the values both are just `std:strings`. So, we might rewrite our request handler as such:

    response hello_world(const endpoint_matches &matches,
                         const query_params     &params)
    {
        std::stringstream body;
        body << "<h1>Hello, World!</h1>\n<ul>\n";

        for(auto& kv : params)
        {
            body << "<li><b>" << kv.first << "</b> " << kv.second << "</li>\n";
        }

        body << "</ul>";
        return {body.str()};
    }



<!-- To begin with, the `luna::server` object is the core of luna—it represents an HTTP server, and it is what determines how endpoints are served.

Endpoints are set up on a `server` with `server::handle_request`. 

    void handle_request(
        request_method method,
        std::string path,
        endpoint_handler_cb callback);

- `method` is the HTTP verb to listen for, _e.g._ GET, POST, PUT, _&c._.
- `path` is the name of the endpoint to listen for, beginning the a `/`. _e.g._ `/documents/`, `"/index.html"`, _&c._
- `callback` is the action to take when the described endpoint is requested (see below).

The `server` stores these endpoints in the order received, and when an HTTP request is made to the server, the first endpoint that matches the endpoint has its callback invoked. No further endpoints will be invoked once a match has been found.

The `callback` parameter is a functional type (_e.g._ a function pointer or lambda) with the signature

    response callback(std::vector<std::string> matches, query_params params)

- `matches` is a vector containing information about how `server` decided this endpoint was the right match. We can ignore this safely for the time being
- `query_params` is a map containing any query parameters (including POST data) that was passed to the endpoint.
- The calback must return a `response` object (see below).

Endpoint callbacks exist primarily to serve data to the HTTP client. At their most basic, they return a string containing HTML to be rendered by a web browser. However, you can also specify the MIME type of the data being returned (for example `"text/json"` if you are returning JSON data), as well as the status code (which defaults to 200 SUCCESS or 201 RESOURCE CREATED).

The simplest callback might look something like this:

    response my_callback(std::vector<endpoint_matches matches,
                                         query_params params)
    {
        return {"<h1>Hello world!</h1>"};
    }

 -->

# TODO 
- endpoint handlers probably also want the request body, not currently being passed in
- no way to construct a response object with binary data, that's a real shame
- responses are constructed in memory. Maybe we don't want that. Mayve we want to provide a hook in a response object for reading data chunks at a time.
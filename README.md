# ScreepsApi
Api Abstraction for Screeps private servers

## Writing implementation for protocol

### Http Api access

The Node class is the base class to map access to javascript routers and should not be used as a base class.

Client class defines the base routing protocol (for the root namespace of the server).
It provides low level access to http requests (Post and Get).
Module class defines nth level namespace based routing protocols.
Api class defines the global access to Screeps Api. It used a WebClient to connect to the server and defines various data access methods.

### Sample

Client class can be used as defined in abstraction or inherited to map javascript top level router.
Each sub-level javascript router is defined as a Module with the upper level Module as parent.
Each module defines its routes by using addRoute method with proper parameters.
Module class can be used as defined in abstraction or inherited to define per router sub-classes.

If the api server provides a "/api/version" route using Get method, you could write :
```cpp
ScreepsApi::Api* screepsapi = ...;
ScreepsApi::Client client = new ScreepsApi::Client ( screepsapi );
ScreepsApi::Module api = new ScreepsApi::Module ( "api", client );
api->addRoute ( "version", ScreepsApi::Web::RoutingMethod::HttpGet, false, "" );
```

using inheritance, this could be wrotten as :
```cpp
namespace ApiVn {
class Api : public ScreepsApi::Api
{
public:
    ...
};
class Client : public ScreepsApi::Client
{
public:
    Client (Api* api) :
        ScreepsApi::Client ( api ),
        m_api ( this )
    {
    }
protected:
    ApiModule m_api;
};
class ApiModule : public ScreepsApi::Module
{
public:
    ApiModule (Client* client) :
        ScreepsApi::Module ( "api", client )
    {
        addRoute ( "version", ScreepsApi::Web::RoutingMethod::HttpGet, false, "" );
    }
};
```

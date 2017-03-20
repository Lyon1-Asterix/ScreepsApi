# ScreepsApi
Api Abstraction for Screeps private servers

## Introduction

### Design Goal

Our goal is to define a C++11 abstraction of the web Api of [Screeps](http://www.screeps.com) game.
This abstraction is designed to be used with private servers using modauth for authentication.

### Usage and dependencies

### Integration

## ToDo

- [x] Node.js router mapping
- [ ] Node.js websocket mapping
- [ ] Api abstraction based on official client protocol
  - [x] signin (modauth)
  - [x] code branch pulling
  - [x] code branch pushing
  - [x] console sandbox
  - [x] partial user data
  - [x] partial room data
  - [ ] retrieve complete user data
  - [ ] retrieve complete world data
  - [ ] retrieve complete room data
- [x] Api manager
- [ ] client subscription and server push manager
- [x] Low level http access
- [ ] Low level ws access

## Class description

### Web abstraction

Api mapping is based on the fact that you provide http client for low level access to the server.
Api is based on the use of an abstraction of these access (defined in [web.hpp](https://github.com/Lyon1-Asterix/ScreepsApi/blob/master/include/ScreepsApi/Web.hpp)).

### Routes and Replies

### Node.js routers mapping

The Node class is the base class to map access to javascript routers and should not be used as a base class.

Client class defines the base routing protocol (for the root namespace of the server).
It provides low level access to http requests (Post and Get).
Module class defines nth level namespace based routing protocols.

### Api abstraction

Api class defines the global access to Screeps Api. It used a WebClient to connect to the server and defines various data access methods.

## Writing implementation for protocol

### Http Api access

Client class can be used as defined in abstraction or inherited to map javascript top level router.
Each sub-level javascript router is defined as a Module with the upper level Module as parent.
Each module defines its routes by using addRoute method with proper parameters.
Module class can be used as defined in abstraction or inherited to define per router sub-classes.

### Sample

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

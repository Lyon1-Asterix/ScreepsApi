#ifndef Screeps_Base_Node_Hpp
#define Screeps_Base_Node_Hpp

#include "ScreepsApi/Reply.hpp"
#include "ScreepsApi/Route.hpp"

#include "nlohmann/json.hpp"

namespace ScreepsApi {

class Api;

class Node
{
    friend class Module;
public:
    Reply route ( std::string name, std::string content = "", Web::RoutingMethod method = Web::RoutingMethod::Default );
    Reply route ( std::string name, nlohmann::json content = {}, nlohmann::json query = {}, Web::RoutingMethod method = Web::RoutingMethod::Default );
    Node& operator [] ( const std::string& name );
protected:
    Node ( std::string prefix, Node* pParent );
    virtual Reply post ( const std::string& url, std::string content, Web::Header header = Web::Header () ) = 0;
    virtual Reply get ( const std::string& url, std::string content, Web::Header header = Web::Header () ) = 0;
    virtual Reply get ( const std::string& url, Web::Header header = Web::Header () ) = 0;

    virtual Reply post ( const std::string& url, nlohmann::json content = {}, nlohmann::json query = {}, Web::Header header = Web::Header () ) = 0;
    virtual Reply get ( const std::string& url, nlohmann::json content = {}, nlohmann::json query = {}, Web::Header header = Web::Header () ) = 0;
protected:
    void addRoute ( std::string name, Web::RoutingMethod method = Web::RoutingMethod::HttpPost, bool doTokenAuth = true, std::string helper = "" );
    std::map < std::string, Route > m_routes;
    std::string m_prefix;
    Node* m_pParent;
    Api* m_pApi;
    std::map < std::string, Node* > m_pChildren;
};

}

#endif

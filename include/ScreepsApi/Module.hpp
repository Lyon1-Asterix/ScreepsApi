#ifndef Screeps_Base_Module_Hpp
#define Screeps_Base_Module_Hpp

#include "ScreepsApi/Reply.hpp"
#include "ScreepsApi/Route.hpp"
#include "ScreepsApi/Node.hpp"

namespace ScreepsApi {

class Module : public Node
{
public:
    Module(std::string prefix, Node* pParent );
    Module& operator [] ( const std::string& name );
protected:
    virtual Reply post ( const std::string& url, std::string content, Web::Header header = Web::Header () );
    virtual Reply get ( const std::string& url, std::string content, Web::Header header = Web::Header () );
    virtual Reply get ( const std::string& url, Web::Header header = Web::Header () );

    virtual Reply post ( const std::string& url, nlohmann::json content = {}, nlohmann::json query = {}, Web::Header header = Web::Header () );
    virtual Reply get ( const std::string& url, nlohmann::json content = {}, nlohmann::json query = {}, Web::Header header = Web::Header () );
    //virtual std::string getToken ();
    //virtual void setToken ( std::string token );
};

}

#endif

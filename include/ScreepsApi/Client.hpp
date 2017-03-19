#ifndef Screeps_Base_Client_Hpp
#define Screeps_Base_Client_Hpp

#include "ScreepsApi/Reply.hpp"
#include "ScreepsApi/Route.hpp"
#include "ScreepsApi/Node.hpp"
#include "ScreepsApi/Api.hpp"

namespace ScreepsApi {

class Client : public Node
{
public:
    Client(Api* pApi);
protected:
    Reply encapsulate (Web::Reply response);
    virtual Reply post ( const std::string& url, std::string content, Web::Header header = Web::Header () );
    virtual Reply get ( const std::string& url, std::string, Web::Header header = Web::Header () );
    virtual Reply get ( const std::string& url, Web::Header header = Web::Header () );
    std::shared_ptr<Web::Client> m_pClient;
    Web::Header m_mHeader;
    Web::Reply m_response;
};

}

#endif

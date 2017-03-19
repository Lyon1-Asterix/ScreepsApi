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
    /*virtual bool Connect ( std::string ticket, bool native ) = 0;
    virtual bool Signin ( std::string email, std::string password ) = 0;
    virtual bool PullCode ( std::string branch ) = 0;
    virtual bool PushCode ( std::string branch ) = 0;
    virtual bool Console ( std::string command ) = 0;
    virtual bool Room ( std::string name ) = 0;*/
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

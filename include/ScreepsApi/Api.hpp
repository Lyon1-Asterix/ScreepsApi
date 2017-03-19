#ifndef Screeps_Base_Api_Hpp
#define Screeps_Base_Api_Hpp

#include "ScreepsApi/Web.hpp"

namespace ScreepsApi {

class Api
{
public:
    Api(std::shared_ptr<Web::Client> pClient);
    virtual bool Signin ( std::string email, std::string password ) = 0;
    virtual bool PullCode ( std::string branch ) = 0;
    virtual bool PushCode ( std::string branch ) = 0;
    virtual bool Console ( std::string command ) = 0;
    virtual bool Room ( std::string name ) = 0;
protected:
    std::shared_ptr<Web::Client> m_pClient;
    std::string m_tokenAuth;
public:
    virtual std::string getToken ();
    virtual void setToken ( std::string token );
    std::shared_ptr<Web::Client> getClient ();
};

}

#endif

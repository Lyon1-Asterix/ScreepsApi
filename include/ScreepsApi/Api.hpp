#ifndef Screeps_Base_Api_Hpp
#define Screeps_Base_Api_Hpp

#include "ScreepsApi/Web.hpp"

#include "nlohmann/json.hpp"

namespace ScreepsApi {

class Api
{
public:
    Api(std::shared_ptr<Web::Client> pClient,std::shared_ptr<Web::Socket> pSocket);
    virtual bool initialized () = 0;
    virtual bool Signin ( std::string email, std::string password ) = 0;
    virtual bool PushCode ( std::string branch, std::map < std::string, std::string > modules ) = 0;
    virtual bool Console ( std::string command ) = 0;
    virtual bool AddSpawn ( std::string name, std::string x, std::string y ) = 0;
    //
    virtual nlohmann::json User () = 0;
    virtual nlohmann::json Room ( std::string name ) = 0;
    virtual nlohmann::json PullCode ( std::string branch ) = 0;
    //
    virtual void ConsoleListener (std::function<void(nlohmann::json)> callback) = 0;
    virtual void RoomListener (std::string room, std::function<void(nlohmann::json)> callback) = 0;
    virtual void WorldListener (std::function<void(nlohmann::json)> callback) = 0;
    virtual void UserListener (std::function<void(nlohmann::json)> callback) = 0;
public:
    virtual std::string getToken ();
    virtual void setToken ( std::string token );
    std::shared_ptr<Web::Client> getClient ();
protected:
    std::shared_ptr<Web::Client> m_pClient;
    std::shared_ptr<Web::Socket> m_pSocket;
    std::string m_tokenAuth;
};

}

#endif

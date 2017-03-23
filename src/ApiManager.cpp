#include "ScreepsApi/ApiManager.hpp"
#include <thread>

namespace ScreepsApi {

ApiManager* ApiManager::m_instance = NULL;

ApiManager& ApiManager::Instance ()
{
    if ( m_instance == NULL )
        m_instance = new ApiManager;
    return *m_instance;
}

void ApiManager::socketProtocolCB ( std::string m )
{
    m_socclient->unsubscribe ( "protocol" );
    socketConnected = true;
}

void ApiManager::socketTimeCB ( std::string m )
{
    m_socclient->subscribe ( "protocol", std::bind ( &ApiManager::socketProtocolCB, this, std::placeholders::_1 ) );
    m_socclient->unsubscribe ( "time" );
}

void ApiManager::initialize ( std::shared_ptr < Web::Client > client,std::shared_ptr<Web::Socket> socket)
{
    m_webclient = NULL;
    m_version = -1;
    client->connect ();
    Web::Reply reply = client->request ( Web::RoutingMethod::HttpGet, "/api/version" );
    nlohmann::json out = nlohmann::json::parse ( reply.content () );
    if ( out.find ( "ok" ) == out.end () ) return;
    if ( out["ok"].get<int>() != 1 ) return;
    m_webclient = client;
    m_socclient = socket;
    m_socclient->subscribe ( "time", std::bind ( &ApiManager::socketTimeCB, this, std::placeholders::_1 ) );
    m_socclient->connect ();
    while ( ! socketConnected ) std::this_thread::sleep_for ( std::chrono::milliseconds ( 5 ) );
    m_version = out["protocol"].get<int> ();
}

std::shared_ptr < Api > ApiManager::getApi ()
{
    std::clog << "Create Api client for protocol " << m_version << std::endl;
    return m_apiImplementations [ m_version ] ( m_webclient, m_socclient );
}

void ApiManager::registerCreator ( int v, Creator c )
{
    m_apiImplementations [ v ] = c;
}

ApiManager::ApiManager () :
    m_webclient ( NULL ),
    m_version ( -1 )
{
}

}

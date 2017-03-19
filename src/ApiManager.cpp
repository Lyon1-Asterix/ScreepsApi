#include "ScreepsApi/ApiManager.hpp"

namespace ScreepsApi {

ApiManager* ApiManager::m_instance = NULL;

ApiManager& ApiManager::Instance ()
{
    if ( m_instance == NULL )
        m_instance = new ApiManager;
    return *m_instance;
}

void ApiManager::initialize ( std::shared_ptr < Web::Client > client )
{
    m_webclient = NULL;
    m_version = -1;
    Web::Reply reply = client->request ( Web::RoutingMethod::HttpGet, "/api/version" );
    nlohmann::json out = nlohmann::json::parse ( reply.content () );
    if ( out.find ( "ok" ) == out.end () ) return;
    if ( out["ok"].get<int>() != 1 ) return;
    m_version = out["protocol"].get<int> ();
    m_webclient = client;
}

std::shared_ptr < Api > ApiManager::getApi ()
{
    std::clog << "Create Api client for protocol " << m_version << std::endl;
    return m_apiImplementations [ m_version ] ( m_webclient );
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

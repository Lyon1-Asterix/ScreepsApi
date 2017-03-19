#include "ScreepsApi/Client.hpp"

namespace ScreepsApi {

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace);

Client::Client(Api* pApi) :
    Node ( "/", NULL )
{
    m_pApi = pApi;
    m_pClient = m_pApi->getClient ();
}

Reply Client::encapsulate (Web::Reply response)
{
    Reply out;
    auto r0=m_response.content ();
    if ( ! response.header ().has("Content-Length") )
    {
        out.type = None;
    }
    else if ( response.header ().has("Content-Type")  )
    {
        auto type = response.header ().get("Content-Type");
        if ( type.find ( "application/json" ) != std::string::npos )
        {
            out.type = Json;
            out.data._json = nlohmann::json::parse ( r0 );
        }
        else if ( type.find ( "image/png" ) != std::string::npos )
        {
            out.type = Png;
            out.data._content = r0;
        }
        else if ( type.find ( "text/html" ) != std::string::npos )
        {
            out.type = Html;
            out.data._html = r0;
        }
        else {
            out.type = Unknown;
            out.data._content = r0;
        }
    }
    else {
    }
    out.m_response = response;
    return out;
}

Reply Client::post ( const std::string& url, std::string content, Web::Header header )
{
    std::string uri = "/" + url;
    header.set ("Content-Type", "application/json; charset=utf-8" );
    m_response = m_pClient->request(Web::RoutingMethod::HttpPost, uri, content,header);
    Reply ret = encapsulate ( m_response );
    return ret;
}

Reply Client::get ( const std::string& url, std::string content, Web::Header header )
{
    std::string uri = "/" + url;
    std::string query = "";
    m_response = m_pClient->request(Web::RoutingMethod::HttpGet, uri, content,header);
    Reply ret = encapsulate ( m_response );
    return ret;
}

Reply Client::get ( const std::string& url, Web::Header header )
{
    std::string uri = "/" + url;
    m_response = m_pClient->request(Web::RoutingMethod::HttpGet, uri, "",header);
    Reply ret = encapsulate ( m_response );
    return ret;
}

}

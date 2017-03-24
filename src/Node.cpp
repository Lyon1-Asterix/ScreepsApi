#include "ScreepsApi/Node.hpp"
#include "ScreepsApi/Api.hpp"

namespace ScreepsApi {

Node::Node ( std::string prefix, Node* pParent ) :
    m_prefix ( prefix ),
    m_pParent ( pParent )
{
    if ( m_pParent != NULL ) {
        m_pParent->m_pChildren [ prefix ] = this;
        m_pApi = m_pParent->m_pApi;
    }
}

Node& Node::operator [] ( const std::string& name )
{
    if ( m_pChildren.find ( name ) != m_pChildren.end () )
        return *(m_pChildren[name]);
}

void Node::addRoute ( std::string name, Web::RoutingMethod method, bool doTokenAuth, std::string helper )
{
    RouteData route = { method, doTokenAuth, name, helper };
    if ( method == Web::RoutingMethod::HttpPost ) m_routes [ name ].post = route;
    else m_routes [ name ].get = route;
}

Reply Node::route ( std::string name, std::string content, Web::RoutingMethod method )
{
    if ( m_routes.find ( name ) != m_routes.end () )
    {
        Route& route = m_routes [ name ];
        RouteData called;
        if ( method == Web::RoutingMethod::Default ) {
            if ( route.get.m_method != Web::RoutingMethod::Default ) called = route.get;
            else if ( route.post.m_method != Web::RoutingMethod::Default ) called = route.post;
        }
        else if ( method == Web::RoutingMethod::HttpGet && route.get.m_method != Web::RoutingMethod::Default ) called = route.get;
        else if ( method == Web::RoutingMethod::HttpPost && route.post.m_method != Web::RoutingMethod::Default ) called = route.post;
        Web::Header header;
        Reply reply;
        if ( called.m_tokenAuth ) {
            header.set ( "X-Token", m_pApi->getToken () );
            header.set ( "X-Username", m_pApi->getToken () );
        }
        if ( called.m_method == Web::RoutingMethod::HttpPost ) {
            reply = post ( called.m_name, content, header );
        } else {
            reply = get ( called.m_name, content, header );
        }
        if ( called.m_tokenAuth ) {
            m_pApi->setToken ( reply.m_response.header ().get("X-Token") );
        }
        return reply;
    }
    return Reply ();
}

Reply Node::route ( std::string name, nlohmann::json content, nlohmann::json query, Web::RoutingMethod method )
{
    if ( m_routes.find ( name ) != m_routes.end () )
    {
        Route& route = m_routes [ name ];
        RouteData called;
        if ( method == Web::RoutingMethod::Default ) {
            if ( route.get.m_method != Web::RoutingMethod::Default ) called = route.get;
            else if ( route.post.m_method != Web::RoutingMethod::Default ) called = route.post;
        }
        else if ( method == Web::RoutingMethod::HttpGet && route.get.m_method != Web::RoutingMethod::Default ) called = route.get;
        else if ( method == Web::RoutingMethod::HttpPost && route.post.m_method != Web::RoutingMethod::Default ) called = route.post;
        Web::Header header;
        Reply reply;
        if ( called.m_tokenAuth ) {
            header.set ( "X-Token", m_pApi->getToken () );
            header.set ( "X-Username", m_pApi->getToken () );
        }
        if ( called.m_method == Web::RoutingMethod::HttpPost ) {
            reply = post ( called.m_name, content, query, header );
        } else {
            reply = get ( called.m_name, content, query, header );
        }
        if ( called.m_tokenAuth ) {
            m_pApi->setToken ( reply.m_response.header ().get("X-Token") );
        }
        return reply;
    }
    return Reply ();
}

}

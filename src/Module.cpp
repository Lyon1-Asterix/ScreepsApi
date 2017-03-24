#include "ScreepsApi/Module.hpp"
 
namespace ScreepsApi {

Module::Module(std::string prefix, Node* pParent ) :
    Node ( prefix, pParent )
{
}

Module& Module::operator [] ( const std::string& name )
{
    return *( dynamic_cast < Module* > ( & Node::operator[](name) ) );
}

Reply Module::post ( const std::string& url, std::string content, Web::Header header )
{
    return m_pParent->post ( m_prefix + "/" + url, content, header );
}

Reply Module::get ( const std::string& url, std::string content, Web::Header header )
{
    return m_pParent->get ( m_prefix + "/" + url, content, header );
}

Reply Module::get ( const std::string& url, Web::Header header )
{
    return m_pParent->get ( m_prefix + "/" + url, header );
}

Reply Module::post ( const std::string& url, nlohmann::json content, nlohmann::json query, Web::Header header )
{
    return m_pParent->post ( m_prefix + "/" + url, content, query, header );
}

Reply Module::get ( const std::string& url, nlohmann::json content, nlohmann::json query, Web::Header header )
{
    return m_pParent->get ( m_prefix + "/" + url, content, query, header );
}

}

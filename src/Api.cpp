#include "ScreepsApi/Api.hpp"

namespace ScreepsApi {

Api::Api(std::shared_ptr<Web::Client> pClient) :
    m_pClient ( pClient )
{
}

std::string Api::getToken ()
{
    return m_tokenAuth;
}

void Api::setToken ( std::string token )
{
    m_tokenAuth = token;
}

std::shared_ptr<Web::Client> Api::getClient ()
{
    return m_pClient;
}

}

#ifndef Screeps_Base_Route_Hpp
#define Screeps_Base_Route_Hpp

#include<string>

#include "ScreepsApi/Web.hpp"

namespace ScreepsApi {

class RouteData
{
public:
    RouteData () : m_method ( Web::RoutingMethod::Default ) {}
    RouteData (Web::RoutingMethod method, bool tokenAuth, std::string name, std::string helper) :
        m_method ( method ),
        m_tokenAuth ( tokenAuth ),
        m_name ( name ),
        m_helper ( helper )
        {}
    Web::RoutingMethod m_method;
    bool m_tokenAuth;
    std::string m_name;
    std::string m_helper;
};

class Route
{
public:
    RouteData get, post;
};

}

#endif

#ifndef Screeps_Base_ApiManager_Hpp
#define Screeps_Base_ApiManager_Hpp

#include <map>

#include "ScreepsApi/Web.hpp"
#include "ScreepsApi/Client.hpp"

namespace ScreepsApi {

class ApiManager
{
public:
    typedef std::function < std::shared_ptr < Api > ( std::shared_ptr < Web::Client > ) > Creator;
public:
    static ApiManager& Instance ();
    void initialize ( std::shared_ptr < Web::Client > client );
    std::shared_ptr < Api > getApi ();
    void registerCreator ( int v, Creator c );
protected:
    ApiManager ();
    std::map < int, Creator > m_apiImplementations;
    std::shared_ptr < Web::Client > m_webclient;
    int m_version;
    static ApiManager* m_instance;
};

}

#endif

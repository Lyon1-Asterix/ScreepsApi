#ifndef Screeps_Base_Web_Hpp
#define Screeps_Base_Web_Hpp

#include<string>
#include<map>
#include <memory>

namespace ScreepsApi {

namespace Web {

typedef enum
{
    Default,
    HttpPost,
    HttpGet
} RoutingMethod;

class Header
{
public:
    virtual std::string get(std::string n) { return m_data[n]; }
    virtual void set(std::string n,std::string v) { m_data[n] = v; }
    virtual bool has(std::string n) { return m_data.find ( n ) != m_data.end (); }
    std::map < std::string, std::string > m_data;
};

class Reply
{
public:
    virtual Header& header () { return m_header; }
    virtual std::string content () { return m_content; }
    Header m_header;
    std::string m_content;
    std::string m_mimetype;
    std::string m_charset;
};

class Client
{
public:
    virtual void connect () = 0;
    virtual void close() = 0;
    virtual Reply request ( RoutingMethod method, std::string uri, std::string content = "", Header header = Header () ) = 0;
};

class Socket
{
public:
    virtual void connect () = 0;
    virtual void close() = 0;
    virtual void send ( std::string message ) = 0;
    virtual void subscribe ( std::string message, std::function<void(std::string)> callback ) = 0;
    virtual void unsubscribe ( std::string message ) = 0;
};

}

}

#endif

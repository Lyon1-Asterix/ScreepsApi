#ifndef Screeps_Base_Reply_Hpp
#define Screeps_Base_Reply_Hpp

#include<string>

#include "ScreepsApi/Web.hpp"

#include "nlohmann/json.hpp"

namespace ScreepsApi {

typedef enum
{
    Json,
    Png,
    Html,
    None,
    Unknown
} ReplyType;

/*
typedef union __ReplyData
{
    struct {
        unsigned char* buffer;
        unsigned int size;
    } _png;
    std::string _html;
    std::string _content;
    ~__ReplyData () {}
    __ReplyData () : _content ( "" ) {}
} ReplyData;
*/

typedef struct __Reply
{
    ReplyType type;
    struct
    {
        struct {
            unsigned char* buffer;
            unsigned int size;
        } _png;
        std::string _html;
        nlohmann::json _json;
        std::string _content;
    } data;
    Web::Reply m_response;
    ~__Reply () {}
    __Reply () : type ( Unknown ) {}
    __Reply (const __Reply& ref ) : type ( ref.type ) {
        if ( type == Json ) data._json = ref.data._json;
        if ( type == Png ) data._content = ref.data._content;
        if ( type == Html ) data._html = ref.data._html;
        if ( type == None ) data._content = ref.data._content;
        if ( type == Unknown ) data._content = ref.data._content;
        m_response = ref.m_response;
    }
} Reply;

}

#endif

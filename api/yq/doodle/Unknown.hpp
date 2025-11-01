////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/DObject.hpp>

namespace yq::doodle {
    struct UnkAny {
        std::string     type;
        std::string     data;
    };


    //! This is an "unknown" object, meant for allowing older versions interact with
    //! newer ones.
    class Unknown : public DObject {
    public:
    
        //std::vector<UValue>     m_unkAttrs;
        
    };
    
}

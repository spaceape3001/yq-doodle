////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/Map.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/string_maps.hpp>

namespace yq::b3 {
    struct Context {
    
        StringMap                           colors;
        Map<std::string,double,IgCase>      units;
        
        const double*       unit(const std::string&) const;
        std::string_view    color(const std::string&) const;
    
        Context();
        ~Context();
    };
}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PyPoint2D.hpp"

namespace yq::doodle {
    uint8_t Point::dimensions(count_k) const
    {
        size_t n    = values(COUNT);
        if(is_attribute("x"))
            n = std::min(1,n);
        if(is_attribute("y"))
            n = std::min(2,n);
        if(is_attribute("z"))
            n = std::min(3,n);
        if(is_attribute("w"))
            n = std::min(4,n);
        if(is_attribute("az"))
            n = std::min(2,n);
        if(is_attribute("el"))
            n = std::min(3,n);
        if(is_attribute("lat"))
            n = std::min(2,n);
        if(is_attribute("lon"))
            n = std::min(3,n);
        if(is_attribute("alt"))
            n = std::min(2,n);
        if(is_attribute("th"))
            n = std::min(2,n);
        return n;
    }
}

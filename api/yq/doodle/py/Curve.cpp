////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Curve.hpp"
#include <doodle/PyMetaWriter.hpp>
#include <algorithm>

YQ_DOODLE_IMPLEMENT(yq::doodle::Curve)

namespace yq::doodle {
    void Curve::init_meta()
    {
        auto w = writer<Curve>();
        w.description("Curve");
        w.attribute("s", "0.");         // need the default here
        w.attribute("s0", "0.");
        w.attribute("s1", "1.");
    }

    uint8_t Curve::dimensions(count_k) const
    {
        size_t  m   = values(COUNT);
        if(m>=255)
            return 0xFF;
        uint8_t n   = (uint8_t) m;
        if(is_attribute("x"))
            n = std::min(n,(uint8_t) 1);
        if(is_attribute("y"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("z"))
            n = std::min(n,(uint8_t) 3);
        if(is_attribute("w"))
            n = std::min(n,(uint8_t) 4);
        if(is_attribute("ang"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("a"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("az"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("el"))
            n = std::min(n,(uint8_t) 3);
        if(is_attribute("lat"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("lon"))
            n = std::min(n,(uint8_t) 3);
        if(is_attribute("alt"))
            n = std::min(n,(uint8_t) 2);
        if(is_attribute("th"))
            n = std::min(n,(uint8_t) 2);
        return n;
    }

                
    Curve::Curve(Project& prj) : Py(prj)
    {
    }
    
    Curve::Curve(CopyAPI& api, const Curve& cp) : Py(api, cp)
    {
    }
    
    Curve::~Curve()
    {
    }
}

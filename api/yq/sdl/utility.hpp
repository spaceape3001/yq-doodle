////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/trait/has_nan.hpp>

namespace yq::sdl {
    inline bool within(double v, double lo, double hi)
    {
        if((!is_nan(lo)) && (v < lo))
            return false;
        if((!is_nan(hi)) && (v > hi))
            return false;
        return true;
    }
}

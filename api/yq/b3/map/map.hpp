////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/typedef.hpp>
#include <yq/units.hpp>
#include <yq/shape/AxBox2.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq::b3 {
    class Doc;
    class PaintDevice;
    
    struct MapParams {
        //  these will be overrides...
        AxBox2D         bounds  = NAN;
        unit::Degree    heading = NAN;
    };

    bool    render_map(Doc&, PaintDevice&, const MapParams& mp={});
}

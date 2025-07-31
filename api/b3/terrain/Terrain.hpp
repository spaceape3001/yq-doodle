////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/Frame.hpp>
#include <yq/shape/AxBox2.hpp>

#ifdef NAN
    #undef NAN
#endif

namespace yq::b3 {
    class Terrain : public Frame {
        YQ_OBJECT_DECLARE(Terrain, Frame)
    public:
        Terrain(const Param&);
        virtual ~Terrain();
        
        const AxBox2D&  bounds() const { return m_bounds; }
        
    private:
        AxBox2D     m_bounds = NAN;
    };
}

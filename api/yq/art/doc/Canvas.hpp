////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/doc/Doc.hpp>
#include <yq/shape/AxBox2.hpp>

namespace yq::art {
    class Canvas : public Doc {
        YQ_OBJECT_DECLARE(Canvas, Doc)
    public:
    
        static void init_meta();
        Canvas();
        ~Canvas();
        
        const AxBox2D&  bounds() const { return m_bounds; }
        void            set_bounds(const AxBox2D&);
        
        static constexpr const AxBox2D  kDefBounds = { {0., 0.}, {1000., 1000.} };
        
    private:
        AxBox2D     m_bounds = kDefBounds;
    };
}

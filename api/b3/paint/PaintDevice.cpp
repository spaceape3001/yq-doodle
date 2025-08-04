////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PaintDevice.hpp"
#include <yq/shape/AxBox2.hpp>
#include <yq/shape/Size2.hxx>
#include <yq/vector/Vector2.hxx>

namespace yq::b3 {
    PaintDevice::PaintDevice() = default;
    PaintDevice::~PaintDevice() = default;
    
    AxBox2D PaintDevice::bounds() const
    {
        return AxBox2D( ZERO, (Vector2D) m_size );
    }
    
}

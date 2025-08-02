////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/Obj.hpp>
#include <yq/shape/Circle2.hpp>

namespace yq::b3 {

    class Circle : public Obj {
        YQ_OBJECT_DECLARE(Circle, Obj)
    public:
        Circle(const Param&);
        ~Circle();
        
        const Circle2D&   circle() const { return m_circle; }
        
    public:
        Circle2D    m_circle;
    };
}

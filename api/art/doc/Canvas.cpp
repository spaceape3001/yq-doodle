////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Canvas.hpp"
#include <art/doc/DocMetaWriter.hpp>
#include <art/tags.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Canvas)

namespace yq::art {
    void Canvas::init_meta()
    {
        auto w = writer<Canvas>();
        w.description("Art Canvas");
        w.property("bounds", &Canvas::m_bounds).def_value(kDefBounds).tag(kTag_Save);
    }
    
    Canvas::Canvas()
    {
    }
    
    Canvas::~Canvas()
    {
    }

    void    Canvas::set_bounds(const AxBox2D&v)
    {
        m_bounds    = v;
        bump();
    }
}

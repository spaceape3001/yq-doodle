////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Canvas2D.hpp"
#include <doodle/space/Space2DMetaWriter.hpp>
#include <doodle/Project.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Canvas2D)

namespace yq::doodle {
    void Canvas2D::init_meta()
    {
        auto w = writer<Canvas2D>();
        w.description("2D Canvas");
    }

    Canvas2D::Canvas2D(Project& prj) : Space2D(prj), Canvas(prj)
    {
        m_margins   = { 13_mm, 13_mm, 13_mm, 13_mm };
        m_pitch     = { 1_mm, 1_mm };
        m_pivot     = { 0., 0. };
//        m_page      = { 200_mm, 260_mm };
        m_pages.lo  = { 0, 0 };
        m_pages.hi  = { 1, 1 };
    }
    
    Canvas2D::Canvas2D(CopyAPI& api, const Canvas2D& cp) : 
        Space2D(api, cp), Canvas(api, cp),
        m_margins(cp.m_margins),
//        m_page(cp.m_page), 
        m_pages(cp.m_pages),
        m_pitch(cp.m_pitch), 
        m_pivot(cp.m_pivot)
    {
        
    }
    
    Canvas2D::~Canvas2D()
    {
    }

    void        Canvas2D::remap(const Remapper& theMap)
    {
        DObject::remap(theMap);
    }
}

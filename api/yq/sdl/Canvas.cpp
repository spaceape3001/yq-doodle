////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Canvas.hpp"
#include <sdl/DObjectMetaWriter.hpp>
#include <sdl/Project.hpp>

YQ_SDL_IMPLEMENT(yq::sdl::Canvas)

namespace yq::sdl {
    void Canvas::init_meta()
    {
        auto w = writer<Canvas>();
        w.description("2D Canvas");
    }

    Canvas::Canvas(Project& prj) : Surface(prj)
    {
        m_margins   = { 13_mm, 13_mm, 13_mm, 13_mm };
        m_pitch     = { 1_mm, 1_mm };
        m_pivot     = { 0., 0. };
//        m_page      = { 200_mm, 260_mm };
        m_pages.lo  = { 0, 0 };
        m_pages.hi  = { 1, 1 };
    }
    
    Canvas::Canvas(CopyAPI& api, const Canvas& cp) : 
        Surface(api, cp),
        m_margins(cp.m_margins),
//        m_page(cp.m_page), 
        m_pages(cp.m_pages),
        m_pitch(cp.m_pitch), 
        m_pivot(cp.m_pivot)
    {
        
    }
    
    Canvas::~Canvas()
    {
    }

    void        Canvas::remap(const Remapper& theMap)
    {
        DObject::remap(theMap);
    }
}

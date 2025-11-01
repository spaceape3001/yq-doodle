////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Drawing.hpp"
#include "DObjectMetaWriter.hpp"
#include "Paper.hpp"
#include <yq/tags.hpp>

YQ_SDL_IMPLEMENT(yq::sdl::Drawing)

#ifdef NAN
    #undef NAN
#endif

namespace yq::sdl {
    void Drawing::init_meta()
    {
        auto w = writer<Drawing>();
        w.description("SDL Drawing");
        w.property("bounds", &Drawing::bounds_ref).setter(&Drawing::set_bounds).tag(kTag_Save);
    }

    Drawing::Drawing(Project&prj) : Surface(prj), m_bounds(ZERO, { kPaper_USLetter.x.value, kPaper_USLetter.y.value })
    {
    }
    
    Drawing::Drawing(CopyAPI&api, const Drawing&cp) : Surface(api, cp), m_bounds(cp.m_bounds)
    {
    }

    Drawing::~Drawing()
    {
    }

    AxBox2D     Drawing::calc(soft_k) const 
    {
        return m_bounds;
    }
    
    AxBox2D     Drawing::calc(hard_k) const
    {
        return NAN;
    }

    void        Drawing::remap(const Remapper& rmap)
    {
        Surface::remap(rmap);
    }

    void        Drawing::set_bounds(const AxBox2D&b)
    {
        m_bounds    = b;
        bump();
    }

}

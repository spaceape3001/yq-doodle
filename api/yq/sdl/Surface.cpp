////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Surface.hpp"
#include "DObjectMetaWriter.hpp"

YQ_SDL_IMPLEMENT(yq::sdl::Surface)

namespace yq::sdl {
    void Surface::init_meta()
    {
        auto w = writer<Surface>();
        w.description("Surface");
    }

    Surface::Surface(Project&prj) : DObject(prj)
    {
    }
    
    Surface::Surface(CopyAPI&api, const Surface&cp) : DObject(api, cp)
    {
    }

    Surface::~Surface()
    {
    }

    AxBox2D     Surface::bounds(hard_k) const
    {
        return calc(HARD);
    }
    
    AxBox2D     Surface::bounds(soft_k) const
    {
        return calc(SOFT);
    }

    //! Remap IDs/pointers appropriately
    void        Surface::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Page2D.hpp"
#include <doodle/2D/Space2DInfoWriter.hpp>
#include <doodle/Project.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Page2D)

namespace yq::doodle {
    void Page2D::init_info()
    {
        auto w = writer<Page2D>();
        w.description("2D Page");
    }

    Page2D::Page2D(Project& prj) : Space2D(prj)
    {
    }
    
    Page2D::Page2D(Project& prj, const Page2D& cp) : Space2D(prj, cp)
    {
        
    }
    
    Page2D::~Page2D()
    {
    }

    void        Page2D::remap(const Remapper& theMap)
    {
        DObject::remap(theMap);
    }
}

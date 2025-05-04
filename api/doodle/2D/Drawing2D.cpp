////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Drawing2D.hpp"
#include <doodle/2D/Space2DInfoWriter.hpp>
#include <doodle/Project.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Drawing2D)

namespace yq::doodle {
    void Drawing2D::init_info()
    {
        auto w = writer<Drawing2D>();
        w.description("2D Drawing");
    }

    Drawing2D::Drawing2D(Project& prj) : Page2D(prj)
    {
    }
    
    Drawing2D::Drawing2D(Project& prj, const Drawing2D& cp) : Page2D(prj, cp)
    {
        
    }
    
    Drawing2D::~Drawing2D()
    {
    }

    void        Drawing2D::remap(const Remapper& theMap)
    {
        DObject::remap(theMap);
    }
}

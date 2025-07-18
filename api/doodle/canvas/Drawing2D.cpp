////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Drawing2D.hpp"
#include <doodle/space/Space2DMetaWriter.hpp>
#include <doodle/Project.hpp>

YQ_OBJECT_IMPLEMENT(yq::doodle::Drawing2D)

namespace yq::doodle {
    void Drawing2D::init_meta()
    {
        auto w = writer<Drawing2D>();
        w.description("2D Drawing");
    }

    Drawing2D::Drawing2D(Project& prj) : Canvas2D(prj)
    {
    }
    
    Drawing2D::Drawing2D(CopyAPI& api, const Drawing2D& cp) : Canvas2D(api, cp)
    {
        
    }
    
    Drawing2D::~Drawing2D()
    {
    }

    void        Drawing2D::remap(const Remapper& theMap)
    {
        DObject::remap(theMap);
    }
    
    
    //Drawing2D   sdraw(Project::testing());
}

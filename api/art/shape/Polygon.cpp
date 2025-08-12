////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polygon.hpp"
#include <art/obj/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Polygon)

namespace yq::art {
    void Polygon::init_meta()
    {
        auto w = writer<Polygon>();
        w.description("Polygon");
    }
    
    Polygon::Polygon(Doc&doc) : Vertices(doc)
    {
    }
    
    Polygon::~Polygon()
    {
    }
}

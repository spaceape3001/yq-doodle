////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polyline.hpp"
#include <art/obj/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Polyline)

namespace yq::art {
    void Polyline::init_meta()
    {
        auto w = writer<Polyline>();
        w.description("Polyline");
    }
    
    Polyline::Polyline(Doc&doc) : Vertices(doc)
    {
    }
    
    Polyline::~Polyline()
    {
    }
}

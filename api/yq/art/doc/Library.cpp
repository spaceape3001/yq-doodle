////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Library.hpp"
#include <yq/art/doc/DocMetaWriter.hpp>
#include <yq/art/tags.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Library)

namespace yq::art {
    void Library::init_meta()
    {
        auto w = writer<Library>();
        w.description("Art Library");
    }
    
    Library::Library()
    {
    }
    
    Library::~Library()
    {
    }
}

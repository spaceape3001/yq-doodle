////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <art/forward.hpp>
#include <yq/core/Ref.hpp>

namespace yq::art {
    //! Adapter so we can dynamically cast something to a art document
    class ArtDocPtr {
    public:
    
        ArtDocPtr();
        ArtDocPtr(DocPtr);
        
        virtual ~ArtDocPtr();
    
        Doc*        doc() { return m_doc.ptr(); }
        const Doc*  doc() const { return m_doc.ptr(); }
        
    protected:
        DocPtr      m_doc;
    };
}

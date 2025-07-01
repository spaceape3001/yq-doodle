////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Association.hpp"
#include "AssociationMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Association)

namespace yq::doodle {
    AssociationMeta::AssociationMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl) : DObjectMeta(zName, base, sl)
    {
        set(Flag::ASSOCIATION);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Association::init_meta()
    {
        auto w = writer<Association>();
        w.description("Association");
    }
    
    Association::Association(Project& prj) : DObject(prj)
    {
    }
    
    Association::Association(CopyAPI& api, const Association& assn) : DObject(api, assn)
    {
    }

    Association::~Association()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Association::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}


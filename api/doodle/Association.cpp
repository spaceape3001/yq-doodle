////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Association.hpp"
#include "AssociationInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Association)

namespace yq::doodle {
    AssociationInfo::AssociationInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl) : DObjectInfo(zName, base, sl)
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


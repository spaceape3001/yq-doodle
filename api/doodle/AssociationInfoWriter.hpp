////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectInfoWriter.hpp>
#include <doodle/Association.hpp>

namespace yq::doodle {
    template <typename T>
    class AssociationInfo::Writer : public DObjectInfo::Writer<T> {
    public:
        Writer(AssociationInfo* aInfo) : DObjectInfo::Writer<T>(aInfo)
        {
        }
        
        Writer(AssociationInfo& aInfo) : Writer(&aInfo)
        {
        }
    };

}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/DObjectMetaWriter.hpp>
#include <yq/doodle/Association.hpp>

namespace yq::doodle {
    template <typename T>
    class AssociationMeta::Writer : public DObjectMeta::Writer<T> {
    public:
        Writer(AssociationMeta* aInfo) : DObjectMeta::Writer<T>(aInfo)
        {
        }
        
        Writer(AssociationMeta& aInfo) : Writer(&aInfo)
        {
        }
    };

}

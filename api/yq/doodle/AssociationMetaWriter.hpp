////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectMetaWriter.hpp>
#include <doodle/Association.hpp>

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

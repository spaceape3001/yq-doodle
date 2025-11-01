////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectMetaWriter.hpp>
#include <doodle/Constraint.hpp>

namespace yq::doodle {
    template <typename T>
    class ConstraintMeta::Writer : public DObjectMeta::Writer<T> {
    public:
        Writer(ConstraintMeta* cInfo) : DObjectMeta::Writer<T>(cInfo)
        {
        }
        
        Writer(ConstraintMeta& cInfo) : Writer(&cInfo)
        {
        }
    };
}

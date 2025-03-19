////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectInfoWriter.hpp>
#include <doodle/Constraint.hpp>

namespace yq::doodle {
    template <typename T>
    class ConstraintInfo::Writer : public DObjectInfo::Writer<T> {
    public:
        Writer(ConstraintInfo* cInfo) : DObjectInfo::Writer<T>(cInfo)
        {
        }
        
        Writer(ConstraintInfo& cInfo) : Writer(&cInfo)
        {
        }
    };
}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Space2DInfoWriter.hpp>
#include <doodle/Space2Z.hpp>

namespace yq::doodle {
    template <typename T>
    class Space2ZInfo::Writer : public Space2DInfo::Writer<T> {
    public:
        Writer(Space2ZInfo* mInfo) : Space2DInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(Space2ZInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}

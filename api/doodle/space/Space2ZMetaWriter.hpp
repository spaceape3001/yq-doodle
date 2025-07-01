////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Space2DMetaWriter.hpp>
#include <doodle/Space2Z.hpp>

namespace yq::doodle {
    template <typename T>
    class Space2ZMeta::Writer : public Space2DMeta::Writer<T> {
    public:
        Writer(Space2ZMeta* mMeta) : Space2DMeta::Writer<T>(mMeta)
        {
        }
        
        Writer(Space2ZMeta& mMeta) : Writer(&mMeta)
        {
        }
    };
}

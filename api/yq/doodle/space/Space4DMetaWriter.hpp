////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/SpaceMetaWriter.hpp>
#include <yq/doodle/space/Space4D.hpp>

namespace yq::doodle {
    template <typename T>
    class Space4DMeta::Writer : public SpaceMeta::Writer<T> {
    public:
        Writer(Space4DMeta* mMeta) : SpaceMeta::Writer<T>(mMeta)
        {
        }
        
        Writer(Space4DMeta& mMeta) : Writer(&mMeta)
        {
        }
    };
}

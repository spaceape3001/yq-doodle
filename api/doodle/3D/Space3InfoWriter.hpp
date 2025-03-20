////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/SpaceInfoWriter.hpp>
#include <doodle/3D/Space3.hpp>

namespace yq::doodle {
    template <typename T>
    class Space3Info::Writer : public SpaceInfo::Writer<T> {
    public:
        Writer(Space3Info* mInfo) : SpaceInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(Space3Info& mInfo) : Writer(&mInfo)
        {
        }
    };
}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectMetaWriter.hpp>
#include <doodle/Portal.hpp>

namespace yq::doodle {
    template <typename T>
    class PortalMeta::Writer : public DObjectMeta::Writer<T> {
    public:
        Writer(PortalMeta* mInfo) : DObjectMeta::Writer<T>(mInfo)
        {
        }
        
        Writer(PortalMeta& mInfo) : Writer(&mInfo)
        {
        }
    };
}

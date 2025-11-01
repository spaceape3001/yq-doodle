////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/DObjectMetaWriter.hpp>
#include <yq/doodle/Portal.hpp>

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

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObjectInfoWriter.hpp>
#include <doodle/Portal.hpp>

namespace yq::doodle {
    template <typename T>
    class PortalInfo::Writer : public DObjectInfo::Writer<T> {
    public:
        Writer(PortalInfo* mInfo) : DObjectInfo::Writer<T>(mInfo)
        {
        }
        
        Writer(PortalInfo& mInfo) : Writer(&mInfo)
        {
        }
    };
}

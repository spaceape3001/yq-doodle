////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Motion.hpp"
#include "MotionInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Motion)

namespace yq::doodle {
    MotionInfo::MotionInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl) : DObjectInfo(zName, base, sl)
    {
        set(Flag::MOTION);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Motion::init_meta()
    {
        auto w = writer<Motion>();
        w.description("Motion");
    }

    Motion::Motion(Project& prj) : DObject(prj)
    {
    }
    
    Motion::Motion(CopyAPI& api, const Motion& cp) : DObject(api, cp)
    {
    }
    
    Motion::~Motion()
    {
    }

    //! Remap IDs/pointers appropriately
    void        Motion::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}


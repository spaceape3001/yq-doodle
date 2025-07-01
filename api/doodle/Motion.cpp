////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Motion.hpp"
#include "MotionMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Motion)

namespace yq::doodle {
    MotionMeta::MotionMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl) : DObjectMeta(zName, base, sl)
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


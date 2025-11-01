////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Camera.hpp"
#include "CameraMetaWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Camera)

namespace yq::doodle {
    CameraMeta::CameraMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl) : DObjectMeta(zName, base, sl)
    {
        set(Flag::CAMERA);
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Camera::init_meta()
    {
        auto w = writer<Camera>();
        w.description("Camera");
    }

    Camera::Camera(Project&prj) : DObject(prj)
    {
    }
    
    Camera::Camera(CopyAPI& api, const Camera&cp) : DObject(api, cp)
    {
    }
    
    Camera::~Camera()
    {
    }

    void        Camera::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}


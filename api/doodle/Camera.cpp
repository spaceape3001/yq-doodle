////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Camera.hpp"
#include "CameraInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Camera)

namespace yq::doodle {
    CameraInfo::CameraInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl) : DObjectInfo(zName, base, sl)
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


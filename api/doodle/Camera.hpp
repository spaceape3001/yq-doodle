////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class CameraInfo : public DObjectInfo {
    public:
        template <typename T> class Writer;
        CameraInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! \brief A camera
    */
    class Camera : public DObject {
        YQ_OBJECT_INFO(CameraInfo)
        YQ_DOODLE_DECLARE(Camera, DObject)
    public:
    
        static void init_info();
    
    protected:
        Camera(Project&);
        Camera(CopyAPI&, const Camera&);
        ~Camera();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Camera(const Camera&) = delete;
        Camera(Camera&&) = delete;
        Camera& operator=(const Camera&) = delete;
        Camera& operator=(Camera&&) = delete;
    };

}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class CameraMeta : public DObjectMeta {
    public:
        template <typename T> class Writer;
        CameraMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! \brief A camera
    */
    class Camera : public DObject {
        YQ_OBJECT_INFO(CameraMeta)
        YQ_DOODLE_DECLARE(Camera, DObject)
    public:
    
        static void init_meta();
    
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

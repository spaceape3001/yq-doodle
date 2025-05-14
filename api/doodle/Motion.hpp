////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class MotionInfo : public DObjectInfo {
    public:
        template <typename T> class Writer;
        MotionInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! \brief A motion

        Motion is dynamic changes to properties.
    */
    class Motion : public DObject {
        YQ_OBJECT_INFO(MotionInfo)
        YQ_OBJECT_DECLARE(Motion, DObject)
    public:

        static void init_info();
    
    protected:
        Motion(Project&);
        Motion(CopyAPI&, const Motion&);
        ~Motion();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&) = 0;
        
        
    private:
        Motion(const Motion&) = delete;
        Motion(Motion&&) = delete;
        Motion& operator=(const Motion&) = delete;
        Motion& operator=(Motion&&) = delete;
    };

}

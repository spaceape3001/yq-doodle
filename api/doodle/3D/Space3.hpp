////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Space.hpp>

namespace yq::doodle {
    class Space3Info : public SpaceInfo {
    public:
        template <typename T> class Writer;
        Space3Info(std::string_view zName, SpaceInfo& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A space 
    
        Defines a 3D space in two dimensions (strict)
    */
    class Space3 : public Space {
        YQ_OBJECT_INFO(Space3Info)
        YQ_OBJECT_DECLARE(Space3, Space)
    public:
    
        static void init_info();
    
    protected:
        Space3(Project&);
        Space3(Project&, const Space3&);
        ~Space3();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Space3(const Space3&) = delete;
        Space3(Space3&&) = delete;
        Space3& operator=(const Space3&) = delete;
        Space3& operator=(Space3&&) = delete;
    };
}

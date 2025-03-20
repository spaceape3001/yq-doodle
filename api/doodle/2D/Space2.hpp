////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Space.hpp>

namespace yq::doodle {
    class Space2Info : public SpaceInfo {
    public:
        template <typename T> class Writer;
        Space2Info(std::string_view zName, SpaceInfo& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A space 
    
        Defines a 2D space in two dimensions (strict)
    */
    class Space2 : public Space {
        YQ_OBJECT_INFO(Space2Info)
        YQ_OBJECT_DECLARE(Space2, Space)
    public:
    
        static void init_info();
    
    protected:
        Space2(Project&);
        Space2(Project&, const Space2&);
        ~Space2();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Space2(const Space2&) = delete;
        Space2(Space2&&) = delete;
        Space2& operator=(const Space2&) = delete;
        Space2& operator=(Space2&&) = delete;
    };
}

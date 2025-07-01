////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/space/Space2D.hpp>

namespace yq::doodle {
    class Space2ZInfo : public Space2DInfo {
    public:
        template <typename T> class Writer;
        Space2ZInfo(std::string_view zName, SpaceMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A 2+Z dimensional space
    
        This defines a space whose major axes are x & y, with a minor axis in z.  
        Think like a floor plan, where a wall can be assumed full height unless
        otherwise noted; or a park map with areas (playgrounds, ponds, moats, 
        aligators, etc).
    */
    class Space2Z : public Space2D {
        YQ_OBJECT_INFO(Space2ZInfo)
        YQ_OBJECT_DECLARE(Space2Z, Space2D)
    public:
    
        static void init_meta();

        virtual bool    supports_2D() const override { return true; }
        virtual bool    supports_3D() const override { return true; }
     
    protected:
        Space2Z(Project&);
        Space2Z(CopyAPI&, const Space2Z&);
        ~Space2Z();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Space2Z(const Space2Z&) = delete;
        Space2Z(Space2Z&&) = delete;
        Space2Z& operator=(const Space2Z&) = delete;
        Space2Z& operator=(Space2Z&&) = delete;
    };
}

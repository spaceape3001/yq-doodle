////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class SpaceMeta : public DObjectMeta {
    public:
        template <typename T> class Writer;
        SpaceMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A space 
    
        Defines a space, coordinate system, including limits.  
        Common coordinate transforms may be set here.
    */
    class Space : public DObject {
        YQ_OBJECT_INFO(SpaceMeta)
        YQ_DOODLE_DECLARE_ABSTRACT(Space, DObject)
    public:
    
        static void init_meta();
    
        virtual bool        supports_1D() const { return false; }
        virtual bool        supports_2D() const { return false; }
        virtual bool        supports_3D() const { return false; }
        virtual bool        supports_4D() const { return false; }
        
    protected:
        Space(Project&);
        Space(CopyAPI&, const Space&);
        ~Space();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
    private:
        Space(const Space&) = delete;
        Space(Space&&) = delete;
        Space& operator=(const Space&) = delete;
        Space& operator=(Space&&) = delete;
    };
}

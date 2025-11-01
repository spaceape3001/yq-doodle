////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/Space.hpp>

namespace yq::doodle {
    class Space1DMeta : public SpaceMeta {
    public:
        template <typename T> class Writer;
        Space1DMeta(std::string_view zName, SpaceMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A space 
    
        Defines a 1D space in one dimension (strict)
    */
    class Space1D : public Space {
        YQ_OBJECT_META(Space1DMeta)
        YQ_OBJECT_DECLARE(Space1D, Space)
    public:
    
        static void init_meta();
    
        virtual bool        supports_1D() const override { return true; }

    protected:
        Space1D(Project&);
        Space1D(CopyAPI&, const Space1D&);
        ~Space1D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Space1D(const Space1D&) = delete;
        Space1D(Space1D&&) = delete;
        Space1D& operator=(const Space1D&) = delete;
        Space1D& operator=(Space1D&&) = delete;
    };
}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class PortalMeta : public DObjectMeta {
    public:
        template <typename T> class Writer;
        PortalMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A portal
    
        A portal is how to bring one space into another...???? (TBD, putting this here for reminder)
    */
    class Portal : public DObject {
        YQ_OBJECT_META(PortalMeta)
        YQ_OBJECT_DECLARE(Portal, DObject)
    public:
    
        static void init_meta();
    
        virtual bool        supports_1D() const { return false; }
        virtual bool        supports_2D() const { return false; }
        virtual bool        supports_3D() const { return false; }
        virtual bool        supports_4D() const { return false; }
        
    protected:
        Portal(Project&);
        Portal(Project&, const Portal&);
        ~Portal();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
    private:
        Portal(const Portal&) = delete;
        Portal(Portal&&) = delete;
        Portal& operator=(const Portal&) = delete;
        Portal& operator=(Portal&&) = delete;
    };
}

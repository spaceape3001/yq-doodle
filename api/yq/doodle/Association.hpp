////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class AssociationMeta : public DObjectMeta {
    public:
        template <typename T> class Writer;
        AssociationMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! An association
    
        An association is basically notes/link to something else.
    */
    class Association : public DObject {
        YQ_OBJECT_META(AssociationMeta)
        YQ_DOODLE_DECLARE(Association, DObject)
    public:

        static void init_meta();
    
    protected:
        Association(Project&);
        Association(CopyAPI&, const Association&);
        ~Association();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Association(const Association&) = delete;
        Association(Association&&) = delete;
        Association& operator=(const Association&) = delete;
        Association& operator=(Association&&) = delete;
    };

}

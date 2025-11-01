////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/doodle/DObject.hpp>

namespace yq::doodle {
    class LightMeta : public DObjectMeta {
    public:
        template <typename T> class Writer;
        LightMeta(std::string_view zName, DObjectMeta& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! \brief A constraint

        A constraint is something that spaces... could be distance, organization, etc.
    */
    class Light : public DObject {
        YQ_OBJECT_META(LightMeta)
        YQ_OBJECT_DECLARE(Light, DObject)
    public:
    
        static void init_meta();
    
    protected:
        Light(Project&);
        Light(CopyAPI&, const Light&);
        ~Light();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&) = 0;
        
        
    private:
        Light(const Light&) = delete;
        Light(Light&&) = delete;
        Light& operator=(const Light&) = delete;
        Light& operator=(Light&&) = delete;
    };
}

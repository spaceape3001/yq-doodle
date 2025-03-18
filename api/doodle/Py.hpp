////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/DObject.hpp>

namespace yq::doodle {
    class PyInfo : public DObjectInfo {
    public:
        template <typename T> class Writer;
        PyInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl=std::source_location::current());
    };
    

    /*! A physical object
    
        This represents a physical object, the number represents the number of coordinates needed to describe it.
    */
    class Py : public DObject {
        YQ_OBJECT_INFO(PyInfo)
        YQ_OBJECT_DECLARE(Py, DObject)
    public:
    
        virtual uint8_t dimensions(count_k) const = 0;
    
        static void init_info();
    
    protected:
        Py(DDocument&);
        Py(DDocument&, const Py&);
        ~Py();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py(const Py&) = delete;
        Py(Py&&) = delete;
        Py& operator=(const Py&) = delete;
        Py& operator=(Py&&) = delete;
    };
}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Py.hpp>

namespace yq::doodle {
    class Py0DInfo : public PyInfo {
    public:
        template <typename T> class Writer;
        Py0DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    /*! A physical object in 0D
    */
    class Py0D : public Py {
        YQ_OBJECT_INFO(Py0DInfo)
        YQ_OBJECT_DECLARE(Py0D, Py)
    public:
    
        virtual uint8_t dimensions(count_k) const final { return 0; }

        static void init_info();

    protected:
        Py0D(Project&);
        Py0D(Project&, const Py0D&);
        ~Py0D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py0D(const Py0D&) = delete;
        Py0D(Py0D&&) = delete;
        Py0D& operator=(const Py0D&) = delete;
        Py0D& operator=(Py0D&&) = delete;
    };

}

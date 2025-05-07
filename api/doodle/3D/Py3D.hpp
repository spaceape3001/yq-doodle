////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Py.hpp>
#include <yq/typedef/vector3.hpp>

namespace yq::doodle {
    class Py3DInfo : public PyInfo {
    public:
        template <typename T> class Writer;
        Py3DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    struct Vector3S {
        std::string x;
        std::string y;
        std::string z;
    };

    /*! A physical object in 3D
    */
    class Py3D : public Py {
        YQ_OBJECT_INFO(Py3DInfo)
        YQ_DOODLE_DECLARE(Py3D, Py)
    public:
    
        virtual uint8_t dimensions(count_k) const final { return 3; }

        static void init_info();
        
        std::string_view    x() const;
        std::string_view    y() const;
        std::string_view    z() const;

    protected:
        Py3D(Project&);
        Py3D(Project&, const Py3D&);
        ~Py3D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py3D(const Py3D&) = delete;
        Py3D(Py3D&&) = delete;
        Py3D& operator=(const Py3D&) = delete;
        Py3D& operator=(Py3D&&) = delete;
    };

}

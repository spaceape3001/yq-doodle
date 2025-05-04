////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Py.hpp>
#include <yq/typedef/vector4.hpp>

namespace yq::doodle {
    class Py4DInfo : public PyInfo {
    public:
        template <typename T> class Writer;
        Py4DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };

    struct Vector4S {
        std::string x;
        std::string y;
        std::string z;
        std::string w;
    };
    
    /*! A physical object in 4D
    */
    class Py4D : public Py {
        YQ_OBJECT_INFO(Py4DInfo)
        YQ_OBJECT_DECLARE(Py4D, Py)
    public:
    
        virtual uint8_t dimensions(count_k) const final { return 4; }

        static void init_info();
        
        std::string_view    x() const;
        std::string_view    y() const;
        std::string_view    z() const;
        std::string_view    w() const;

    protected:
        Py4D(Project&);
        Py4D(Project&, const Py4D&);
        ~Py4D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py4D(const Py4D&) = delete;
        Py4D(Py4D&&) = delete;
        Py4D& operator=(const Py4D&) = delete;
        Py4D& operator=(Py4D&&) = delete;
    };

}

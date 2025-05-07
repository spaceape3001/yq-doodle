////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Py.hpp>
#include <yq/typedef/vector2.hpp>

namespace yq::doodle {
    class Py2DInfo : public PyInfo {
    public:
        template <typename T> class Writer;
        Py2DInfo(std::string_view zName, PyInfo& base, const std::source_location& sl=std::source_location::current());
    };
    
    struct Vector2S {
        std::string x;
        std::string y;
    };

    /*! A physical object in 2D
    */
    class Py2D : public Py {
        YQ_OBJECT_INFO(Py2DInfo)
        YQ_DOODLE_DECLARE(Py2D, Py)
    public:
    
        virtual uint8_t dimensions(count_k) const final { return 2; }

        static void init_info();
        
        std::string_view    x() const;
        std::string_view    y() const;

    protected:
        Py2D(Project&);
        Py2D(Project&, const Py2D&);
        ~Py2D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Py2D(const Py2D&) = delete;
        Py2D(Py2D&&) = delete;
        Py2D& operator=(const Py2D&) = delete;
        Py2D& operator=(Py2D&&) = delete;
    };

}

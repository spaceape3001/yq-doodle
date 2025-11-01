////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <art/obj/Obj.hpp>
#include <art/shape/vertex.hpp>

namespace yq::art {
    class Shape : public Obj {
        YQ_OBJECT_DECLARE(Shape, Obj)
    public:
        
        static void init_meta();
    
        Shape(Doc&);
        ~Shape();
        
        // Override for your shape....
        
        virtual size_t          vertex(count_k) const { return 0; }
        
        //! Informational to whether vertices can be appended if count is less than maximum
        //! (This is to inform UI decisions, thus it'll return TRUE on full containers}
        virtual bool            vertex(appendable_k) const { return false; }
        
        //! Informational to whether vertices can be erased if count is greater than zero
        //! (This is to inform UI decisions, thus it'll return TRUE on an empty container.)
        virtual bool            vertex(erasable_k) const { return false; }
        
        //! TRUE means our count isn't fixed
        virtual bool            vertex(count_k, dynamic_k) const { return false; }
        
        //! Minimum point count for shape to be considered "valid" with dynamic counts
        virtual size_t          vertex(count_k, minimum_k) const { return 0; }

        //! Maximum point count for shapeto be considered "valid" with dynamic counts
        virtual size_t          vertex(count_k, maximum_k) const { return SIZE_MAX; }

        virtual const vertex_t* vertex(size_t) const { return nullptr; }
        virtual bool            vertex(size_t, erase_k) { return false; }
        virtual bool            vertex(size_t, set_k, const vertex_t&) { return false; }
        virtual bool            vertex(append_k, const vertex_t&) { return false; }
        
    protected:
        virtual void    save_to(XmlNode&) const override;
        virtual bool    load_from(const XmlNode&) override;
    };
}


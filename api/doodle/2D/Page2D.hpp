////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/2D/Space2D.hpp>

namespace yq::doodle {
    /*! A page type of thing (drawing, diagram, etc)
    */
    class Page2D : public Space2D {
        YQ_OBJECT_DECLARE(Page2D, Space2D)
    public:
    
        static void init_info();
        
    protected:
        Page2D(Project&);
        Page2D(Project&, const Page2D&);
        ~Page2D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Page2D(const Page2D&) = delete;
        Page2D(Page2D&&) = delete;
        Page2D& operator=(const Page2D&) = delete;
        Page2D& operator=(Page2D&&) = delete;
        
    };
}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/2D/Page2D.hpp>

namespace yq::doodle {
    /*! A drawing
    
        Defines a drawing (ie... a reference frame... could be 3D projected into 2D, or simple 2D)
    */
    class Drawing2D : public Page2D {
        YQ_OBJECT_DECLARE(Drawing2D, Page2D)
    public:
    
        static void init_info();
        
    protected:
        Drawing2D(Project&);
        Drawing2D(Project&, const Drawing2D&);
        ~Drawing2D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        
    private:
        Drawing2D(const Drawing2D&) = delete;
        Drawing2D(Drawing2D&&) = delete;
        Drawing2D& operator=(const Drawing2D&) = delete;
        Drawing2D& operator=(Drawing2D&&) = delete;
        
    };
}

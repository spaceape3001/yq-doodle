////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/canvas/Canvas2D.hpp>

namespace yq::doodle {
    /*! A drawing
    
        Defines a drawing (ie... a reference frame... could be 3D projected into 2D, or simple 2D)
    */
    class Drawing2D : public Canvas2D {
        YQ_DOODLE_DECLARE(Drawing2D, Canvas2D)
    public:
    
        static void init_info();

    protected:
        Drawing2D(Project&);
        Drawing2D(CopyAPI&, const Drawing2D&);
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

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/2D/Space2D.hpp>
#include <doodle/Canvas.hpp>
#include <yq/units.hpp>

namespace yq::doodle {
    /*! A page type of thing (drawing, diagram, etc)
    */
    class Canvas2D : public Space2D, public Canvas {
        YQ_DOODLE_DECLARE(Canvas2D, Space2D)
    public:
    
        static void init_info();
        
        //! How "big" a pixel is
        //const Vector2MM&        pitch() const { return m_pitch; }
        //void                    set_pitch(unit::Millimeter);
        
        //const AxBox2MM&         page_size() const { return m_pageSize; }
        
        //! Number of pages (axial box to allow the user to decide to move things before/above existing page with negatives)
        //const AxBox2I&          pages() const { return m_pages; }
        
    protected:
        Canvas2D(Project&);
        Canvas2D(Project&, const Canvas2D&);
        ~Canvas2D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        //Vector2MM           m_pageSize; 
        //AxBox2I             m_pages;
        //Vector2MM           m_pitch;
        
    private:
        Canvas2D(const Canvas2D&) = delete;
        Canvas2D(Canvas2D&&) = delete;
        Canvas2D& operator=(const Canvas2D&) = delete;
        Canvas2D& operator=(Canvas2D&&) = delete;
        
    };
}

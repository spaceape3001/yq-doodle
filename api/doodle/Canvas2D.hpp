////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <doodle/Space2D.hpp>
#include <doodle/Canvas.hpp>
#include <yq/units.hpp>
#include <yq/shape/AxSide2.hpp>

namespace yq::doodle {
    /*! A page type of thing (drawing, diagram, etc)
    */
    class Canvas2D : public Space2D, public Canvas {
        YQ_DOODLE_DECLARE(Canvas2D, Space2D)
    public:
    
        static void init_info();
        
        unit::Millimeter        margin_east() const { return m_margins.hx; }
        unit::Millimeter        margin_north() const { return m_margins.hy; }
        unit::Millimeter        margin_south() const { return m_margins.ly; }
        unit::Millimeter        margin_west() const { return m_margins.lx; }
        
        //! How "big" a pixel is
        const Vector2MM&        pitch() const { return m_pitch; }
        void                    set_pitch(unit::Millimeter);
        
        //! Where to expand from (usually 0,0) when it matters
        const Vector2D&         pivot() const { return m_pivot; }
        
        //const AxBox2MM&         page_size() const { return m_pageSize; }
        
        //! Number of pages (axial box to allow the user to decide to move things before/above existing page with negatives)
        const AxBox2I&          pages() const { return m_pages; }
        
    protected:
        Canvas2D(Project&);
        Canvas2D(CopyAPI&, const Canvas2D&);
        ~Canvas2D();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        AxSide2MM           m_margins;
        AxBox2I             m_pages;
        Vector2MM           m_pitch;
        Vector2D            m_pivot;  
        
    private:
        Canvas2D(const Canvas2D&) = delete;
        Canvas2D(Canvas2D&&) = delete;
        Canvas2D& operator=(const Canvas2D&) = delete;
        Canvas2D& operator=(Canvas2D&&) = delete;
        
    };
}

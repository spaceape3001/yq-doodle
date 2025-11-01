////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sdl/Surface.hpp>
#include <yq/units.hpp>
#include <yq/shape/AxSide2.hpp>

/*
    CANVAS is TODO.... (want paging, etc)
*/

namespace yq::sdl {
    /*! A page type of thing (drawing, diagram, etc)
    */
    class Canvas : public Surface {
        YQ_SDL_DECLARE(Canvas, Surface)
    public:
    
        static void init_meta();
        
        unit::Millimeter        margin_east() const { return m_margins.hx; }
        unit::Millimeter        margin_north() const { return m_margins.hy; }
        unit::Millimeter        margin_south() const { return m_margins.ly; }
        unit::Millimeter        margin_west() const { return m_margins.lx; }

        //! Origin....
        const Vector2D&         origin() const { return m_origin; }
        void                    set_origin(const Vector2D&);

        //! How "big" a pixel is
        const Vector2MM&        pitch() const { return m_pitch; }
        void                    set_pitch(unit::Millimeter);
        
        //! Where to expand from (usually 0,0) when it matters
        //const Vector2D&         pivot() const { return m_pivot; }
        //void                    set_pivot(const Vector2D&);
        
        //! Page size
        const Size2MM&          page_size() const { return m_pageSize; }
        void                    set_page_size(const Size2MM&);
        
        //! Number of pages (axial box to allow the user to decide to move things before/above existing page with negatives)
        const AxBox2I&          pages() const { return m_pages; }
        void                    set_pages(const AxBox2I&);
        
    protected:
        Canvas(Project&);
        Canvas(CopyAPI&, const Canvas&);
        ~Canvas();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);
        
        AxSide2MM           m_margins;
        AxBox2I             m_pages;
        Size2MM             m_pageSize;
        Vector2D            m_origin;
        Vector2MM           m_pitch;
        Vector2D            m_scale;
        //Vector2D            m_pivot;  
        
        virtual AxBox2D     calc(soft_k) const = 0;
        virtual AxBox2D     calc(hard_k) const = 0;

    private:
        Canvas(const Canvas&) = delete;
        Canvas(Canvas&&) = delete;
        Canvas& operator=(const Canvas&) = delete;
        Canvas& operator=(Canvas&&) = delete;
        
    };
}

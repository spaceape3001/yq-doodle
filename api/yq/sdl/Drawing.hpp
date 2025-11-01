////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Surface.hpp"
#include <yq/shape/AxBox2.hpp>

namespace yq::sdl {
    class Drawing : public Surface {
        YQ_SDL_DECLARE(Drawing, Surface)
    public:
        
        static void init_meta();
        
        const AxBox2D&  bounds_ref() const { return m_bounds; }
        void            set_bounds(const AxBox2D&);
        
    protected:
        Drawing(Project&);
        Drawing(CopyAPI&, const Drawing&);
        ~Drawing();

        //! Remap IDs/pointers appropriately
        virtual void        remap(const Remapper&);

        virtual AxBox2D     calc(soft_k) const override;
        virtual AxBox2D     calc(hard_k) const override;
        
    private:
        AxBox2D         m_bounds;
    };
}

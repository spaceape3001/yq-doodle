////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/keywords.hpp>
#include <b3/util/types.hpp>
#include <yq/container/Stack.hpp>
#include <yq/tensor/Tensor24.hpp>
#include <yq/tensor/Tensor23.hpp>
#include <yq/typedef/axbox2.hpp>
#include <variant>

namespace yq::b3 {
    class PaintDevice;
    class Point;
    
    class Painter {
    public:

        using vertex_t  = std::variant<Vector2D, Vector3D, const Point*>;

        const Brush&        brush() const { return m_state.brush; }
        PaintDevice&        device() { return m_paint; }
        const Font&         font() const { return m_state.font; }
        
        const Pen&          pen() const { return m_state.pen; }
    
        //! Restores to a prior state
        //! \note If stack is empty, will not restore to nothing
        void                restore();
        
        Vector2D            operator()(const Vector2D&) const;
        Vector2D            operator()(const Vector3D&) const;
        Vector2D            operator()(const Point&) const;
        Vector2D            operator()(const vertex_t&) const;
        
        
        Vector2D            map(const Vector2D&) const;
        Vector2D            map(const Vector3D&) const;
        Vector2D            map(const Point&) const;
        Vector2D            map(const vertex_t&) const;
        

        void                set_brush(const Brush&);
        void                set_pen(const Pen&);
        void                set_font(const Font&);

        //! Saves the current state
        void                stash();
        
        //! This is used to convert painter coordinates into device coordinates.
        const Tensor24D&    proj3() const { return m_proj3; }

        
        struct Projection2DOpts {
            unit::Degree        heading     = NAN;      //!< Heading for "up"
            AspectRatioPolicy   resizing    = AspectRatioPolicy::Ignore;    //!< How to treat bounds/size mismatch
            bool                vertflip    = true;     //!< true to make +y go up
        };
    
        //! Sets the projection (note, kinda useless w/o bounds & paint device size)
        void                set_proj2(const AxBox2D&, const Projection2DOpts&);  
        
        //  TODO... 3D
        
    protected:
        virtual Vector2D    mapper(const Vector3D&) const;

        struct State {
            Brush           brush;
            Font            font;
            Pen             pen;
        };
        

        Painter(PaintDevice&);
        ~Painter();

        PaintDevice&    m_paint;
        Stack<State>    m_states;
        State           m_state;
        Tensor24D       m_proj3;
        bool            m_vertflip      = false;
        bool            m_distortion    = false;
    };
}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/keywords.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/typedef/axbox2.hpp>
#include <yq/typedef/circle2.hpp>
#include <yq/typedef/rectangle2.hpp>
#include <yq/typedef/segment2.hpp>
#include <yq/typedef/vector2.hpp>
#include <span>
#include <string_view>

#ifdef NAN
    #undef NAN
#endif

namespace yq::b3 {

    struct Brush;
    struct Font;
    struct Pen;
    struct Transform;

    //! Basics to painting (allows for SVG/PNG/etc)
    //! \note This API to remain *SIMPLE* and defaulted
    //! \note Paint Devices will generally be left-handled (ie, top is -y, right is +x)
    class PaintDevice {
    public:
    
        //! Always given, set to things that override
        struct Data {
            const Brush*        brush       = nullptr;
            const Font*         font        = nullptr;
            const Pen*          pen         = nullptr;
            const Transform*    transform   = nullptr;
        };
    
        virtual void                rectangle(const AxBox2D&, const Data&) {}
        virtual void                rectangle(const Rectangle2D&, const Data&);
        virtual void                circle(const Circle2D&, const Data&) {}
        virtual void                ellipse(const AxBox2D&, const Data&) {}
        virtual void                line(const Segment2D&, const Data&) {}
        
        //  Starts a new transform
        virtual void                group(std::string_view, const Data& d){}
        
        //!  Ends a tranform
        virtual void                group(pop_k){}
        
        virtual bool                pixelated() const = 0;
        
        virtual void                polyline(const std::span<const Vector2D>, const Data&){}
        virtual void                polygon(const std::span<const Vector2D>, const Data&){}

        virtual const Size2D&       size() const { return m_size; }
        
        //! Sets the size (note... negatives will be quashed, ie sign flipped)
        virtual void                set_size(const Size2D&){}
        
        AxBox2D                     bounds() const;

    protected:
        PaintDevice();
        ~PaintDevice();
        
        //! Bounds to the paint device...
        Size2D                      m_size = NAN;
    };
}

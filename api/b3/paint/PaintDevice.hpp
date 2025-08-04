////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/keywords.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/typedef/circle2.hpp>
#include <yq/typedef/segment2.hpp>
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
    
        virtual void                circle(const Circle2D&, const Data& d) {}
        virtual void                line(const Segment2D&, const Data& d) {}
        
        //  Starts a new transform
        virtual void                group(std::string_view, const Data& d){}
        
        //!  Ends a tranform
        virtual void                group(pop_k){}
        
        virtual bool                pixelated() const = 0;

        virtual const Size2D&       size() const { return m_size; }
        
        //! Sets the size (note... negatives will be quashed, ie sign flipped)
        virtual void                set_size(const Size2D&){}

    protected:
        PaintDevice(){}
        ~PaintDevice(){}
        
        //! Bounds to the paint device...
        Size2D                      m_size = NAN;
    };
}

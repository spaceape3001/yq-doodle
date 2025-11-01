////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/Frame.hpp>
#include <yq/b3/spatial/PointLine.hpp>

namespace yq::b3 {
    class Polyline : public Frame, public PointLine {
        YQ_OBJECT_DECLARE(Polyline, Frame)
    public:
        Polyline(const Param&, bool);
        ~Polyline();
        
        bool    closed() const { return m_closed; }
        
    private:
        bool    m_closed    = false;
    };
}

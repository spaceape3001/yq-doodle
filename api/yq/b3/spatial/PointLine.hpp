////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/util/ArgList.hpp>

namespace yq::b3 {
    class Point;
    class Frame;
    
    //! Line of points.
    //! \note This is meant to be a side-cart tag-along to the inheritance,
    //! therefore, it's not an object
    class PointLine {
    public:
    
        PointLine(Frame*, const ArgList& pts={});
        virtual ~PointLine();

        unit::Degree        heading(end_k) const;
        bool                heading(valid_k) const;
        
        double              length() const;
        Vector<Vector3D>    outline(double hw=0.) const;

        void                point(add_k, Point*);
        Point*              point(last_k, size_t n=0);
        const Point*        point(last_k, size_t n=0) const;
        Point*              point(size_t);
        const Point*        point(size_t) const;

        const auto&         points() const { return m_points; }
        size_t              points(count_k) const;

    private:
        Vector<Point*>  m_points;
    };
}

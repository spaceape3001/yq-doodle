////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PointLine.hpp"
#include <yq/b3/Frame.hpp>
#include <yq/b3/spatial/Point.hpp>
#include <yq/math/trigonometry.hpp>
#include <yq/vector/Vector2.hxx>
#include <yq/vector/Vector3.hxx>

namespace yq::b3 {
    PointLine::PointLine(Frame* frame, const ArgList& pts)
    {
        if(!frame)
            return;

        for(const std::string& s : pts.values){
            Obj*     obj = frame->find(s);
            if(!obj)
                continue;
            
            Point*      pt    = dynamic_cast<Point*>(obj);
            if(!pt)
                continue;

            m_points << pt;
        }
    }
    
    PointLine::~PointLine()
    {
    }
    
    unit::Degree    PointLine::heading(end_k) const
    {
        if(!heading(VALID))
            return { NAN };
        Vector3D    dd  = point(LAST) -> define() - point(LAST,1) -> define();
        return atan(dd.x, dd.y);
    }

    bool            PointLine::heading(valid_k) const
    {
        return m_points.size() >= 2;
    }
    
    double              PointLine::length() const
    {
        if(m_points.size() <= 1)
            return 0.;
        double  s = 0.;
        for(size_t n=0;n<(m_points.size()-1);++n)
            s += (m_points[n+1]->global() - m_points[n]->global()).length();
        return s;
    }
    
    Vector<Vector3D>    PointLine::outline(double hw) const
    {
        Vector<Vector3D>  ret, left;
        if(m_points.size() > 1){
            for(size_t n=0;n<m_points.size();++n){
                //  And we're assuming x-y primary
                Vector3D       a   = n ? m_points[n-1]->global() : m_points[n]->global();
                Vector3D       b   = n ? m_points[n]->global() : m_points[n+1]->global();
                Vector2D       dx  = ~(b-a).xy();
                Vector3D       dv( -dx.y, dx.x, 0. );
                
                if(n){
                    ret  << (b - dv * hw);
                    left << (b + dv * hw);
                } else {
                    ret  << (a - dv * hw);
                    left << (a + dv * hw);
                }
            }
            
            ret.insert(ret.end(), left.rbegin(), left.rend());
        }
        return ret;
    }

    
    void    PointLine::point(add_k, Point*pt)
    {
        if(pt)
            m_points << pt;
    }

    const Point*  PointLine::point(last_k, size_t n) const
    {
        if(n >= m_points.size())
            return nullptr;
        return *(m_points.rbegin()+n);
    }
    
    Point*  PointLine::point(last_k, size_t n) 
    {
        if(n >= m_points.size())
            return nullptr;
        return *(m_points.rbegin()+n);
    }

    Point*          PointLine::point(size_t n)
    {
        if(n>=m_points.size())
            return nullptr;
        return m_points[n];
    }
    
    const Point*    PointLine::point(size_t n) const
    {
        if(n>=m_points.size())
            return nullptr;
        return m_points[n];
    }
    
    size_t  PointLine::points(count_k) const
    {
        return m_points.size();
    }
}

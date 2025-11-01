////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/Obj.hpp>
#include <yq/b3/spatial/PointType.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Vector3.hpp>

namespace yq::b3 {
    
    class Parser;
    class PointLine;
    
    class Point : public Obj {
        YQ_OBJECT_DECLARE(Point, Obj)
    public:
        Point(const Param&);
        Point(const Vector2D&, const Param&);
        Point(const Vector3D&, const Param&);
        
        virtual ~Point();
        void calc_points() override;
        
        const Vector3D&     define() const { return m_define; }
        const Vector3D&     global() const { return m_global; }
        
        Vector2D            global2D() const { return { m_global.x, m_global.y }; }
        
        double              x() const { return m_global.x; }
        double              y() const { return m_global.y; }
        double              z() const { return m_global.z; }
        
        PointType           type() const { return m_type; }
        
    private:
        PointType           m_type;
        Vector3D            m_define = {};
        Vector3D            m_global = {};
        Vector<PointLine*>  m_attached;
        
        bool    _use();
        bool    _map();
        bool    _list();
    };

    bool    add_box_points(Parser&, Frame* parent, const ArgList& pArgs, const ArgMap&, const std::string& id ={});
}

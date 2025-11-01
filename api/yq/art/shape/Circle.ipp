////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Circle.hpp"
#include <yq/art/tags.hpp>
#include <yq/art/obj/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Circle)

namespace yq::art {
    void Circle::init_meta()
    {
        auto w = writer<Circle>();
        w.description("Circle");
        w.property("radius", &Circle::m_radius).description("Radius").tag(kTag_Save);
    }
        
    Circle::Circle(Doc& doc) : Shape(doc)
    {
    }
    
    Circle::~Circle()
    {
    }

    void    Circle::save_to(XmlNode&xn) const
    {
        Shape::save_to(xn);
        write_vertices(xn, {&m_center});
    }
    
    bool    Circle::load_from(const XmlNode&xn)
    {
        bool success    = Shape::load_from(xn);
        success         = read_vertices(xn, {&m_center});
        return success;
    }

    const vertex_t* Circle::vertex(size_t n) const 
    { 
        switch(n){
        case 0:
            return &m_center;
        default:
            return nullptr; 
        }
    }
    
    bool            Circle::vertex(size_t n, set_k, const vertex_t&v) 
    { 
        switch(n){
        case 0:
            m_center = v;
            return true;
        default:
            return false;
        }
    }
}

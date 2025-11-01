////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Triangle.hpp"
#include <yq/art/obj/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Triangle)

namespace yq::art {
    void Triangle::init_meta()
    {
        auto w = writer<Triangle>();
        w.description("Triangle");
    }
        
    Triangle::Triangle(Doc& doc) : Shape(doc)
    {
    }
    
    Triangle::~Triangle()
    {
    }

    void    Triangle::save_to(XmlNode&xn) const
    {
        Shape::save_to(xn);
        write_vertices(xn, {&m_a, &m_b, &m_c});
    }
    
    bool    Triangle::load_from(const XmlNode&xn)
    {
        bool success    = Shape::load_from(xn);
        success         = read_vertices(xn, {&m_a, &m_b, &m_c});
        return success;
    }

    const vertex_t* Triangle::vertex(size_t n) const 
    { 
        switch(n){
        case 0:
            return &m_a;
        case 1:
            return &m_b;
        case 2:
            return &m_c;
        default:
            return nullptr; 
        }
    }
    
    bool            Triangle::vertex(size_t n, set_k, const vertex_t&v) 
    { 
        switch(n){
        case 0:
            m_a = v;
            return true;
        case 1:
            m_b = v;
            return true;
        case 2:
            m_c = v;
            return true;
        default:
            return false;
        }
    }
}

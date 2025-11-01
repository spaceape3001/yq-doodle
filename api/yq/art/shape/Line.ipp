////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Line.hpp"
#include <yq/art/obj/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Line)

namespace yq::art {
    void Line::init_meta()
    {
        auto w = writer<Line>();
        w.description("Line");
    }
        
    Line::Line(Doc& doc) : Shape(doc)
    {
    }
    
    Line::~Line()
    {
    }

    void    Line::save_to(XmlNode&xn) const
    {
        Shape::save_to(xn);
        write_vertices(xn, {&m_a, &m_b});
    }
    
    bool    Line::load_from(const XmlNode&xn)
    {
        bool success    = Shape::load_from(xn);
        success         = read_vertices(xn, {&m_a, &m_b});
        return success;
    }

    const vertex_t* Line::vertex(size_t n) const 
    { 
        switch(n){
        case 0:
            return &m_a;
        case 1:
            return &m_b;
        default:
            return nullptr; 
        }
    }
    
    bool            Line::vertex(size_t n, set_k, const vertex_t&v) 
    { 
        switch(n){
        case 0:
            m_a = v;
            return true;
        case 1:
            m_b = v;
            return true;
        default:
            return false;
        }
    }
}

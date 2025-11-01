////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Box.hpp"
#include <yq/art/obj/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Box)

namespace yq::art {
    void Box::init_meta()
    {
        auto w = writer<Box>();
        w.description("Box");
    }
        
    Box::Box(Doc& doc) : Shape(doc)
    {
    }
    
    Box::~Box()
    {
    }

    void    Box::save_to(XmlNode&xn) const
    {
        Shape::save_to(xn);
        write_vertices(xn, {&m_a, &m_b});
    }
    
    bool    Box::load_from(const XmlNode&xn)
    {
        bool success    = Shape::load_from(xn);
        success         = read_vertices(xn, {&m_a, &m_b});
        return success;
    }

    const vertex_t* Box::vertex(size_t n) const 
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
    
    bool            Box::vertex(size_t n, set_k, const vertex_t&v) 
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

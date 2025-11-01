////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Vertices.hpp"
#include <art/obj/ObjMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::art::Vertices)

namespace yq::art {
    void Vertices::init_meta()
    {
        auto w = writer<Vertices>();
        w.abstract();
        w.description("Vertices");
    }
    
    Vertices::Vertices(Doc& doc) : Shape(doc)
    {
    }
    
    Vertices::~Vertices()
    {
    }

    void    Vertices::save_to(XmlNode&xn) const 
    {
        Shape::save_to(xn);
        write_vertices(xn, m_vertices);
    }
    
    bool    Vertices::load_from(const XmlNode&xn) 
    {
        bool success    = Shape::load_from(xn);
        success = read_vertices(xn, m_vertices) && success;
        return success;
    }

    size_t          Vertices::vertex(count_k) const
    {
        return m_vertices.size();
    }
    
    const vertex_t* Vertices::vertex(size_t n) const
    {
        if(n < m_vertices.size())
            return &m_vertices[n];
        return nullptr;
    }
    
    bool            Vertices::vertex(size_t n, erase_k)
    {
        if(n<m_vertices.size()){
            m_vertices.erase_at(n);
            return true;
        } else
            return false;
        
    }
    
    bool            Vertices::vertex(size_t n, set_k, const vertex_t& v)
    {
        if(n<m_vertices.size()){
            m_vertices[n]   = v;
            return true;
        } else
            return false;
    }
    
    bool            Vertices::vertex(append_k, const vertex_t&v)
    {
        m_vertices.push_back(v);
        return true;
    }
}

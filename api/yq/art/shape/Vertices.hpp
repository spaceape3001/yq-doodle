////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <art/shape/Shape.hpp>

namespace yq::art {
    //! Abstract shape that's a collection of vertices (ie... common base to polygon & polyline)
    class Vertices : public Shape {
        YQ_OBJECT_DECLARE(Vertices, Shape)
    public:
        
        static void init_meta();
        
        Vertices(Doc&);
        ~Vertices();

        virtual size_t          vertex(count_k) const;
        virtual bool            vertex(appendable_k) const { return true; }
        virtual bool            vertex(count_k, dynamic_k) const { return true; }
        virtual bool            vertex(erasable_k) const { return true; }

        virtual const vertex_t* vertex(size_t) const;
        virtual bool            vertex(size_t, erase_k);
        virtual bool            vertex(size_t, set_k, const vertex_t&);
        virtual bool            vertex(append_k, const vertex_t&);
        
        const auto& vertices() const { return m_vertices; }
        
    protected:
        virtual void            save_to(XmlNode&) const override;
        virtual bool            load_from(const XmlNode&) override;

    private:
        Vector<vertex_t>    m_vertices;
    };
}

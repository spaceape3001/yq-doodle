////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/art/shape/Shape.hpp>

namespace yq::art {
    class Triangle : public Shape {
        YQ_OBJECT_DECLARE(Triangle, Shape)
    public:
        
        static void init_meta();
        
        Triangle(Doc&);
        ~Triangle();

        virtual size_t          vertex(count_k) const override { return 3; }
        
        virtual const vertex_t* vertex(size_t) const;
        virtual bool            vertex(size_t, set_k, const vertex_t&);

        const vertex_t& a() const { return m_a; }
        const vertex_t& b() const { return m_b; }
        const vertex_t& c() const { return m_c; }
        
    protected:
        virtual void    save_to(XmlNode&) const override;
        virtual bool    load_from(const XmlNode&) override;
    private:
        vertex_t    m_a, m_b, m_c;
    };
}

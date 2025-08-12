////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <art/shape/Shape.hpp>

namespace yq::art {

    /*! \brief Two point box
    
        This is a box defined by two corners.
    */
    class Box : public Shape {
        YQ_OBJECT_DECLARE(Box, Shape)
    public:
        
        static void init_meta();
        
        Box(Doc&);
        ~Box();

        virtual size_t          vertex(count_k) const override { return 2; }
        
        virtual const vertex_t* vertex(size_t) const;
        virtual bool            vertex(size_t, set_k, const vertex_t&);

        const vertex_t& a() const { return m_a; }
        const vertex_t& b() const { return m_b; }
        
    protected:
        virtual void    save_to(XmlNode&) const override;
        virtual bool    load_from(const XmlNode&) override;
    private:
        vertex_t    m_a, m_b;
    };
}

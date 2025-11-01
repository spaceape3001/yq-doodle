////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <art/shape/Shape.hpp>

namespace yq::art {

    /*! \brief A circle
    
        This is the simplest definition, a circle defined by a center & a radius.
        Others... will either be an agent or another class.
    */
    class Circle : public Shape {
        YQ_OBJECT_DECLARE(Circle, Shape)
    public:
        
        static void init_meta();
        
        Circle(Doc&);
        ~Circle();
        
        virtual size_t          vertex(count_k) const override { return 1; }
        virtual const vertex_t* vertex(size_t) const;
        virtual bool            vertex(size_t, set_k, const vertex_t&);

        const vertex_t&         center() const { return m_center; }
        double                  radius() const { return m_radius; }
        
    protected:
        virtual void    save_to(XmlNode&) const override;
        virtual bool    load_from(const XmlNode&) override;
        
    private:
        vertex_t    m_center;
        double      m_radius    = 0.;
    };
}

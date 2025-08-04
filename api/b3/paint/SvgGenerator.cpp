////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SvgGenerator.hpp"

#include <b3/util/types.hpp>
#include <yq/shape/Circle2.hpp>
#include <yq/shape/Segment2.hpp>
#include <yq/xml/XmlUtils.hpp>

#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Circle2.hxx>
#include <yq/shape/Segment2.hxx>
#include <yq/vector/Vector2.hxx>

namespace yq::b3 {

    void SvgGenerator::_write(XmlNode&x, const Data&pd, bool cantFill)
    {
        if(pd.transform)
            _write(x, *pd.transform);
        if(pd.font)
            _write(x, *pd.font);
        if(pd.pen)
            _write(x, *pd.pen);
        if(!cantFill){
            if(pd.brush){
                _write(x, *pd.brush);
            } else {
                write_attribute(x, "fill", "none"sv);
            }
        }
    }
    

    void    SvgGenerator::_write(XmlNode&x, const Brush& b)
    {
        if(b.color.def.empty()){
            write_attribute(x, "fill", "none"sv);
        } else {
            write_attribute(x, "fill", b.color.def);
        }
    }
    
    void    SvgGenerator::_write(XmlNode&x, const Font&f)
    {
        // TODO
    }

    void    SvgGenerator::_write(XmlNode&x, const Pen&p)
    {
        if(p.color.def.empty())
            return;
        write_attribute(x, "stroke", p.color.def);
        if(p.width > 0.)
            write_attribute(x, "stroke-width", p.width);
    }

    void    SvgGenerator::_write(XmlNode&x, const Transform&t)
    {
        //  TODO
    }

    ////////////////////////////////////////////////////////////////////////////

    SvgGenerator::SvgGenerator() : PaintDevice()
    {
        xml_start(m_xml);
        m_root      = m_xml.create_element("svg");
        m_current   = m_root;
    }
    
    SvgGenerator::~SvgGenerator()
    {
    }

    void    SvgGenerator::_pop()
    {
        if(!m_nodes.empty())
            m_current   = m_nodes.pop();
    }
    
    void    SvgGenerator::_push(XmlNode*x)
    {
        m_nodes << m_current;
        m_current   = x;
    }

    void    SvgGenerator::circle(const Circle2D&v, const Data& d) 
    {
        if(is_nan(m_bounds)){
            m_bounds    = v.bounds();
        } else {
            m_bounds |= v.bounds();
        }
        
        XmlNode&    x   = *m_current->create_element("circle");
        write_attribute(x, "cx", v.center.x);
        write_attribute(x, "cy", v.center.y);
        write_attribute(x, "r", fabs(v.radius));
        _write(x, d);
    }

    void    SvgGenerator::group(std::string_view id, const Data&d) 
    {
        XmlNode*    x   = m_current -> create_element("g");
        _push(x);
        if(!id.empty())
            write_attribute(*x, "id", id);
        _write(*x, d);
    }
    
    void    SvgGenerator::group(pop_k) 
    {
        _pop();
    }

    void    SvgGenerator::line(const Segment2D& v, const Data& d)
    {
        if(is_nan(m_bounds)){
            m_bounds    = v.bounds();
        } else {
            m_bounds |= v.bounds();
        }
        
        XmlNode&    x   = *m_current->create_element("line");
        write_attribute(x, "x1", v.a.x);
        write_attribute(x, "y1", v.a.y);
        write_attribute(x, "x2", v.b.x);
        write_attribute(x, "y2", v.b.y);
        _write(x, d, true);
    }

    std::error_code    SvgGenerator::save_to(const std::filesystem::path& fp) const
    {
        return save_file(m_xml, fp);
    }

    void               SvgGenerator::set_size(const Size2D& sz) 
    {
        m_size.x    = fabs(sz.x);
        m_size.y    = fabs(sz.y);
        if(!m_width)
            m_width = m_root->create_attribute("width");
        if(!m_height)
            m_height = m_root->create_attribute("height");
        write_x(*m_width, m_size.x);
        write_x(*m_height, m_size.y);
    }
}


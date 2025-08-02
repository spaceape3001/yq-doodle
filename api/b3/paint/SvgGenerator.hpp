////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/paint/PaintDevice.hpp>
#include <yq/container/Stack.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/typedef/xml.hpp>
#include <rapidxml.hpp>
#include <filesystem>

#ifdef NAN
    #undef NAN
#endif

namespace yq::b3 {
    class SvgGenerator : public PaintDevice {
    public:
        SvgGenerator();
        ~SvgGenerator();
        
        std::error_code     save_to(const std::filesystem::path&) const;
        
        void                circle(const Circle2D&, const Data&) override;
        void                group(std::string_view, const Data&) override;
        void                group(pop_k) override;
        void                line(const Segment2D&, const Data&) override;
        
        virtual bool        pixelated() const override { return false; }
        
    private:
        AxBox2D             m_bounds    = NAN;
        XmlDocument         m_xml;
        XmlNode*            m_root      = nullptr;
        XmlAttribute*       m_width     = nullptr;
        XmlAttribute*       m_height    = nullptr;
        XmlAttribute*       m_viewBox   = nullptr;
        XmlNode*            m_current   = nullptr;
        Stack<XmlNode*>     m_nodes;
        
        void    _push(XmlNode*);
        void    _pop();
        
        static void _write(XmlNode&, const Data&, bool cantFill=false);
        static void _write(XmlNode&, const Brush&);
        static void _write(XmlNode&, const Font&);
        static void _write(XmlNode&, const Pen&);
        static void _write(XmlNode&, const Transform&);
    };
}

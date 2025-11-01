////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/paint/PaintDevice.hpp>
#include <yq/container/Stack.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/typedef/xml.hpp>
#include <rapidxml.hpp>
#include <filesystem>

#ifdef NAN
    #undef NAN
#endif

namespace yq { class ByteArray; }

namespace yq::b3 {
    class SvgGenerator : public PaintDevice {
    public:
        SvgGenerator();
        ~SvgGenerator();
        
        virtual bool        pixelated() const override { return false; }
        std::error_code     save_to(const std::filesystem::path&) const;
        ByteArray           export_bytes() const;
        
        void                set_size(const Size2D&) override;

        using PaintDevice::rectangle;
        
        void                circle(const Circle2D&, const Data&) override;
        void                ellipse(const AxBox2D&, const Data&) override;
        void                group(std::string_view, const Data&) override;
        void                group(pop_k) override;
        void                line(const Segment2D&, const Data&) override;
        void                polygon(const std::span<const Vector2D>, const Data&) override;
        void                polyline(const std::span<const Vector2D>, const Data&) override;
        void                rectangle(const AxBox2D&, const Data&) override;
        
        
    private:
        XmlDocument         m_xml;
        XmlNode*            m_root      = nullptr;
        XmlAttribute*       m_width     = nullptr;
        XmlAttribute*       m_height    = nullptr;
        XmlNode*            m_current   = nullptr;
        Stack<XmlNode*>     m_nodes;
        
        void    _push(XmlNode*);
        void    _pop();
        
        static void _write(XmlNode&, const Data&, bool cantFill=false);
        static void _write(XmlNode&, const Brush&);
        static void _write(XmlNode&, const Font&);
        static void _write(XmlNode&, const Pen&);
        static void _write(XmlNode&, const Transform&);
        
        static void _write(XmlBase&, const std::span<const Vector2D>);
    };
}

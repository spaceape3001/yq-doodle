////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Doc.hpp"

#include <art/logging.hpp>
#include <art/tags.hpp>
#include <art/doc/DocMetaWriter.hpp>
#include <art/obj/Obj.hpp>
#include <yq/container/ByteArray.hpp>
#include <yq/core/Any.hpp>
#include <yq/file/FileUtils.hpp>
#include <yq/text/chars.hpp>
#include <yq/xml/XmlUtils.hpp>

#include <yq/meta/Init.hpp>

#include <format>

YQ_OBJECT_IMPLEMENT(yq::art::Doc)
YQ_TYPE_IMPLEMENT(yq::art::ID)
YQ_TYPE_IMPLEMENT(yq::art::Key)
YQ_TYPE_IMPLEMENT(yq::art::Reference)

namespace yq::art {
    struct Doc::Repo {
        Map<std::string_view,const DocMeta*>    byTag;
        MetaLookup<DocMeta>                     lookup;
    };

    const std::vector<const DocMeta*>& DocMeta::all()
    {
        return Doc::repo().lookup.all;
    }

    DocMeta::DocMeta(std::string_view zName, AbstractMeta& base, const std::source_location& sl) :
        AbstractMeta(zName, base, sl)
    {
        m_docTag    = std::format("YQArt{}", stem());
        auto& _r = Doc::repo();
        _r.byTag[m_docTag]  = this;
        _r.lookup << this;
    }

////////////////////////////////////////////////////////////////////////////////
    const DocMeta*  Doc::find_by_xml_tag(std::string_view t)
    {
        return repo().byTag.get(t, nullptr);
    }

    void Doc::init_meta()
    {
        {
            auto w  = writer<ID>();
            w.description("Cross reference identifier");
            w.casts<Reference>();
        }
        
        {
            auto w = writer<Key>();
            w.description("User defined key");
            w.casts<Reference>();
        }
        
        {
            auto w = writer<Reference>();
            w.description("Reference to something else");
        }

        {
            auto w = writer<Doc>();
            w.description("Art document");
            w.property("title", &Doc::m_title);
        }
    }
    
    Doc::Repo& Doc::repo()
    {
        static Repo s_repo;
        return s_repo;
    }
    
////////////////////////////////////////////////////////////////////////////////

    Doc::Doc()
    {
        m_objects.push_back(nullptr);
    }
    
    Doc::~Doc()
    {
        for(auto& obj : m_zombies){
            if(obj){
                delete obj;
                obj     = nullptr;
            }
        }
        m_zombies.clear();

        for(auto& obj : m_objects){
            if(obj){
                delete obj;
                obj     = nullptr;
            }
        }
        m_objects.clear();
    }

    ID    Doc::_insert(Obj* obj)
    {
        if(!obj)
            return {};
            
        if(m_load){                     // used during loading
            m_objects[m_load]   = obj;
            return { m_load };
        }    
        
        id_t    n   = m_objects.size();
        m_objects.push_back(obj);
        return { n };
    }

    bool       Doc::is_empty() const
    {
        for(const Obj* obj : m_objects)
            if(obj)
                return false;
        return m_title.empty() && base_empty();
    }

    Obj*       Doc::object(ID i)
    {
        if(i.id>=m_objects.size())
            return nullptr;
        return m_objects[i.id];
    }
    
    const Obj*  Doc::object(ID i) const
    {
        if(i.id>=m_objects.size())
            return nullptr;
        return m_objects[i.id];
    }
    
    void        Doc::set_title(std::string_view t)
    {
        m_title = std::string(t);
        //bump();
    }

    bool        Doc::valid(ID i) const
    {
        return (i.id<m_objects.size()) && m_objects[i.id];
    }
    
////////////////////////////////////////////////////////////////////////////////
//  XML I/O


    void        Doc::save_to(XmlNode&xn) const
    {
        Abstract::save_to(xn);
        write_attribute(xn, "n", m_objects.size());
        for(const Obj* obj : m_objects){
            if(!obj)
                continue;
            auto& xc    = *xn.create_element(obj->metaInfo().stem());
            obj->save_to(xc);
        }
    }
    
    bool        Doc::load_from(const XmlNode&xn) 
    {
        bool success    =  Abstract::load_from(xn);
        auto n  = read_attribute(xn, "n", x_uint64);
        if(n)
            m_objects.resize(*n, nullptr);
        for(const XmlNode* x = xn.first_node(); x; x = x -> next_sibling()){
            if(!is_upper(x->name()[0]))
                continue;
            const ObjMeta*  om  = Obj::find_by_xml_tag(x->name());
            if(!om){
                artWarning << "Tag " << om->name() << " is not a valid object, skipping";
                continue;
            }
        }
        
        
        return success;
    }

    DocPtr       Doc::load_xml(const XmlDocument& xdoc)
    {
        for(const XmlNode* xn = xdoc.first_node(); xn; xn=xn->next_sibling()){
            if(const DocMeta* dm = find_by_xml_tag(xn->name())){
                Object* obj = dm -> create();
                if(!obj)
                    continue;
                DocPtr   doc = dynamic_cast<Doc*>(obj);
                if(!doc){
                    delete obj;
                    continue;
                }
                if(!doc->load_from(*xn))
                    artWarning << "Xml document didn't fully load successfully";
                return doc;
            }
        }
        
        return {};
    }

    bool        Doc::save_xml(XmlDocument& doc) const
    {
        XmlNode&    root    = *doc.create_element(metaInfo().doc_tag());
        save_to(root);
        return true;
    }


    DocPtr       Doc::load_xml(const std::filesystem::path& file)
    {
        XmlDocument xdoc;
        if(read_file(xdoc, file) != std::error_code())
            return {};
        return load_xml(xdoc);
    }

    DocPtr       Doc::load_xml(const ByteArray& bytes)
    {
        ByteArray       copy    = bytes;
        copy << '\0';
        XmlDocument     doc;
        try {
            doc.parse<0>(copy.data());
        }
        catch(const rapidxml::parse_error&pe){
            size_t  pt  = pe.where<char>() - copy.data();
            artError << "Xml parse error: " << pe.what() << " (at byte " << pt << ")";
            return {};
        }
        
        return load_xml(doc);
    }

    bool         Doc::save_xml(const std::filesystem::path& fp) const
    {
        ByteArray       bytes;
        save_xml(bytes);
        return file_write(fp, bytes);
    }

    bool         Doc::save_xml(ByteArray&bytes) const
    {
        XmlDocument     doc;
        xml_start(doc);
        save_xml(doc);
        bytes   = save_bytes(doc);
        return true;
    }


}

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <art/forward.hpp>
#include <art/keywords.hpp>
#include <art/obj/Abstract.hpp>
#include <yq/core/AllLocal.hpp>
#include <yq/core/Ref.hpp>
#include <filesystem>

namespace yq::art {
    class DocMeta : public AbstractMeta {
    public:
        template <typename> class Writer;
        
        DocMeta(std::string_view zName, AbstractMeta& base, const std::source_location& sl=std::source_location::current());
        
        std::string_view    doc_tag() const { return m_docTag; }
        
        static const std::vector<const DocMeta*>& all();
        
    private:
        std::string     m_docTag;
    };
    
    template <typename> class DocFixer;

    //! This is a drawing or something....
    class Doc : public Abstract, public RefCount {
        YQ_OBJECT_META(DocMeta);
        YQ_OBJECT_FIXER(DocFixer)
        YQ_OBJECT_DECLARE(Doc, Abstract)
    public:
    
        static void init_meta();
    
        //! Filepath that we were loaded from (can be set)
        //! \note Empty for something that's newly created
        const std::filesystem::path&    file() const { return m_file; }
        
        static const DocMeta*           find_by_xml_tag(std::string_view);
        
        void    set_file(const std::filesystem::path&);
        
            //////////////////////////////////////////////////////
            //  GETTERS/INFORMATION

        bool                is_empty() const;
        std::string_view    title() const { return m_title; }
        
            //////////////////////////////////////////////////////
            //  SETTERS
        
        void                set_title(std::string_view);
        
            //////////////////////////////////////////////////////
            //  OBJECTS

        //! Used when you need a *specific* pointer for temporary use
        //! \note this isn't guarded, so document/objects can be erased
        Obj*                object(ID);

        //! Used when you need a *specific* pointer for temporary use
        //! \note this isn't guarded, so document/objects can be erased
        const Obj*          object(ID) const;

        bool                valid(ID) const;

            //////////////////////////////////////////////////////
            //  IO

        static DocPtr       load_xml(const std::filesystem::path&);
        static DocPtr       load_xml(const ByteArray&);
        static DocPtr       load_xml(const XmlDocument&);

        bool                save_xml(const std::filesystem::path&) const;
        bool                save_xml(ByteArray&) const;
        
        //  Will insert a root node
        bool                save_xml(XmlDocument&) const;
        
        //! If there's a current filename, will save to it
        bool                save() const;
        
        Doc();
        virtual ~Doc();
        
    protected:
    
        virtual void        save_to(XmlNode&) const override;
        virtual bool        load_from(const XmlNode&) override;

    private:
        friend class DocMeta;
        friend class Obj;
        
        struct Repo;
        static Repo& repo();
        
        ID                      _insert(Obj*);
        
        std::vector<Obj*>           m_objects;
        std::vector<Obj*>           m_zombies;    //! Erased objects, but retained until the document is destroyed
        std::filesystem::path       m_file;
        std::string                 m_title;
        id_t                        m_load  = 0;

        //  Will likely add "include"/"reference" files (later)

        
        Doc(const Doc&) = delete;
        Doc(Doc&&) = delete;
        Doc& operator=(const Doc&) = delete;
        Doc& operator=(Doc&&) = delete;
    };

}

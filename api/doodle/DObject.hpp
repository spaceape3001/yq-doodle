////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/AllLocal.hpp>
#include <yq/core/Object.hpp>
#include <doodle/bit/SStringMap.hpp>
#include <doodle/bit/Dim.hpp>
#include <doodle/bit/ID.hpp>
#include <doodle/typedef/revision.hpp>
#include <doodle/typedef/dobject.hpp>
#include <doodle/keywords.hpp>
#include <yq/typedef/xml.hpp>
#include <unordered_map>

namespace yq::doodle {
    class DObject;
    class Project;
    struct Remapper;
    template <typename Obj> class DObjectFixer;
    
    class DObjectInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;
        
        DObjectInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());

        Object* create() const override { return nullptr; }
        virtual DObject* create(Project&) const = 0;
        virtual DObject* copy(Project&, const DObject&) const = 0;

        DimFlags    supports() const { return m_supports; }

        bool    is_0d() const;
        bool    is_1d() const;
        bool    is_2d() const;
        bool    is_3d() const;
        bool    is_4d() const;
        bool    is_5d() const;
        bool    is_6d() const;

        static const DObjectInfo*       lookup(std::string_view);

    protected:
        DimFlags    m_supports;
    };
    
    class DObject : public Object {
        YQ_OBJECT_INFO(DObjectInfo)
        YQ_OBJECT_FIXER(DObjectFixer)
        YQ_OBJECT_DECLARE(DObject, Object)
        friend class Project;
    public:

        //! Attribute on THIS object
        std::string_view    attribute(const std::string&) const;
        //! Attribute (either this object or parent or project)
        std::string_view    attribute(const std::string&, all_k) const;
        void                attribute_erase(const std::string&);
        string_set_t        attribute_keys() const;
        void                attribute_set(const std::string&, const std::string&);
        void                attribute_set(const std::string&, std::string&&);
        const string_map_t& attributes() const;
        
        std::span<const ID> children() const { return m_children; }
        
        const std::string&  description() const { return m_description; }
        
        Project&          project() { return m_prj; }
        const Project&    project() const { return m_prj; }

        //! TRUE if this is an attribute on THIS object
        bool                is_attribute(const std::string&) const;

        constexpr ID        id() const { return m_id; }
        ID                  parent() const { return m_parent; }
        const DObject*      parent(pointer_k) const;
        DObject*            parent(pointer_k);
        const std::string&  notes() const { return m_notes; }
        const std::string&  title() const { return m_title; }
        const std::string&  uid() const { return m_uid; }

        void    set_description(const std::string&);
        void    set_notes(const std::string&);
        void    set_uid(const std::string&);
        void    set_title(const std::string&);

        static void init_info();
        
        
        //! Marks this item as having changed
        void    bump();
        
        revision_t  revision(all_k) const { return m_revision[ALL]; }
        revision_t  revision(local_k) const { return m_revision[LOCAL]; }
        
        DObject*    create(child_k, const DObjectInfo&);
        
        template <SomeDObject S>
        S*          create(child_k)
        {
            return static_cast<S*>(create(CHILD, meta<S>()));
        }

    protected:
    
        DObject(Project&);
        DObject(Project&, const DObject&);
        ~DObject();

        //! Remap IDs/pointers appropriately (call base class first)
        virtual void            remap(const Remapper&);

        virtual void            save(XmlNode&) const {}
        virtual bool            load(const XmlNode&) { return true; }

    private:
        friend class DObjectInfo;
        
        DObject(const DObject&) = delete;
        DObject(DObject&&) = delete;
        DObject& operator=(const DObject&) = delete;
        DObject& operator=(DObject&&) = delete;

        Project&                m_prj;
        const ID                m_id;
        SStringMap              m_attributes;
        ID                      m_parent;
        std::vector<ID>         m_children;
        std::string             m_title;
        std::string             m_description;
        std::string             m_uid;
        std::string             m_notes;
        AllLocal<revision_t>    m_revision  = {};
        
        ID::id_t        get_id() const { return m_id.id; }
        
        uint64_t        get_revision() const { return m_revision.all; }
        
        struct Repo;
        static Repo& repo();
    };
    
    struct Remapper {
        std::unordered_map<ID::id_t, ID::id_t>    data;
        ID operator()(ID) const;
    };
}

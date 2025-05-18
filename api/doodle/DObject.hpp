////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/AllLocal.hpp>
#include <yq/core/Object.hpp>
#include <doodle/bit/Dim.hpp>
#include <doodle/bit/ID.hpp>
#include <doodle/bit/SStringMap.hpp>
#include <doodle/typedef/revision.hpp>
#include <doodle/typedef/dobject.hpp>
#include <doodle/keywords.hpp>
#include <yq/typedef/string_vectors.hpp>
#include <yq/typedef/xml.hpp>
#include <unordered_map>
#include <map>

namespace yq::doodle {
    class DObject;
    class Project;
    struct Remapper;
    template <typename Obj> class DObjectFixer;
    
    struct DObjectCopyAPI;
    
    class DObjectInfo : public ObjectInfo {
    public:
        template <typename C> class Writer;
        
        DObjectInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());

        Object* create() const override { return nullptr; }
        virtual DObject* create(Project&) const = 0;
        virtual DObject* copy(DObjectCopyAPI&, const DObject&) const = 0;

        DimFlags    supports() const { return m_supports; }

        bool    is_0d() const;
        bool    is_1d() const;
        bool    is_2d() const;
        bool    is_3d() const;
        bool    is_4d() const;
        bool    is_5d() const;
        bool    is_6d() const;

        static const DObjectInfo*           lookup(std::string_view);
        
        //! TRUE if there's a default attribute
        bool                has_default_attribute(std::string_view) const;

        string_view_set_t           default_attribute_keys() const;

    protected:
        friend class DObject;
        
        virtual void    sweep_impl() override;

        using function_attribute_t      = std::function<std::string_view(const DObject*)>;
        //using function2_attribute_t     = std::function<std::string(const DObject*)>;
        using default_attribute_t       = std::variant<std::monostate, std::string_view, function_attribute_t>;
        using default_attribute_map_t   = std::map<std::string_view, default_attribute_t, IgCase>;
    
        DimFlags                m_supports;
        default_attribute_map_t m_attributes;
        
    };

    #define YQ_DOODLE_DECLARE(cls, base)                    \
        YQ_OBJECT_DECLARE(cls,base)                         \
        friend class DObjectFixer<cls>;                     \
        static constexpr bool   kAbstract       = false;

    #define YQ_DOODLE_DECLARE_ABSTRACT(cls, base) \
        YQ_OBJECT_DECLARE(cls,base)   \
        friend class DObjectFixer<cls>; \
        static constexpr bool   kAbstract       = true;

    /*! \brief Doodle Object
    
        \note attributes/properties should be generic 
        (with advanced capabilities to decode)
    */
    class DObject : public Object {
        YQ_OBJECT_INFO(DObjectInfo)
        YQ_OBJECT_FIXER(DObjectFixer)
        YQ_DOODLE_DECLARE_ABSTRACT(DObject, Object)
        friend class Project;
    public:
    
        /*
        
            Attributes are how things are defined on the objects...
            generally reserved attributes are
            
            a       dimension (so for circles, radius)
            
            az      angle (in degrees) in the x-y plane
            th      angle (in radians) in the x-y plane
            r       distance from origin
            el      elevation angle (in degrees) from the x-y plane      
            
            la      latitude (in degrees)
            lo      longitude (in degrees)
            h       height
            
            s       parametric attribute (can be a range for curves, or singular)
            s0      starting S-value (for curves)
            s1      ending S-value (for curves)
            
            pt      reference point (but keep orientation to parent)
            ref     reference frame (orientation in new space)
            
            w       width
            x       position in x (these take precedence, if defined)
            y       position in y (these take precedence, if defined)
            z       position in z (these take precedence, if defined)
        */
    

        //! Attribute for this object (either local, default, or global)
        std::string_view        attribute(const std::string&) const;
        
        //! Attribute that's a default
        std::string_view        attribute(default_k, const std::string&) const;
        
        //! Attribute (ONLY) on this object
        //! \note This excludes any "default"
        std::string_view        attribute(local_k, const std::string&) const;

        std::string_view        attribute(global_k, const std::string&) const;
        
        void                    attribute_erase(const std::string&);
        string_set_t            attribute_keys() const;
        void                    attribute(set_k, const std::string&, const std::string&);
        void                    attribute(set_k, const std::string&, std::string&&);
        const string_map_t&     attributes() const;
        
        std::span<const ID>     children() const { return m_children; }
        
        const std::string&      description() const { return m_description; }
        
        Project&                project() { return m_project; }
        const Project&          project() const { return m_project; }

        //! TRUE if this is a valid attribute (local, default, or global)
        bool                    is_attribute(const std::string&) const;
        
        //! TRUE if this is a valid "default" attribute
        bool                    is_attribute(default_k, const std::string&) const;
        
        //! TRUE if this is a valid attribute on the global map
        bool                    is_attribute(global_k, const std::string&) const;

        //! TRUE if this is a valid attribute on our map
        bool                    is_attribute(local_k, const std::string&) const;

        constexpr ID            id() const { return m_id; }
        ID                      parent() const { return m_parent; }
        const DObject*          parent(pointer_k) const;
        DObject*                parent(pointer_k);
        const std::string&      notes() const { return m_notes; }
        const std::string&      title() const { return m_title; }
        const std::string&      uid() const { return m_uid; }

        size_t                  values(count_k) const { return m_values.size(); }
        
        const string_vector_t&  values() const { return m_values; }

        void                    value(push_k, std::string&&);
        void                    value(push_k, const std::string&);

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

        using CopyAPI = DObjectCopyAPI;

    protected:
    
        DObject(Project&);
        DObject(CopyAPI&, const DObject&);
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

    protected:
        Project&                m_project;
        const ID                m_id;
        SStringMap              m_attributes;
        string_vector_t         m_values;           // positional data (depends on the object)
        ID                      m_parent;
        std::vector<ID>         m_children;
        std::string             m_title;
        std::string             m_description;
        std::string             m_uid;
        std::string             m_notes;
    
    private:
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

    struct DObjectCopyAPI {
        Project&    project;    //!< New project
        Remapper    mapper;
    };

}

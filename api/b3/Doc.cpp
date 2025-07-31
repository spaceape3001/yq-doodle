////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Doc.hpp"
#include "Frame.hxx"

#include <b3/logging.hpp>
#include <b3/ObjMetaWriter.hpp>
#include <b3/spatial/Point.hpp>
#include <b3/terrain/Terrain.hpp>

#include <yq/file/FileUtils.hpp>
#include <yq/shape/AxBox2.hxx>
#include <yq/vector/Vector3.hxx>

YQ_OBJECT_IMPLEMENT(yq::b3::Doc)

namespace yq::b3 {
    struct Doc::Handler {
        std::string         key;
        std::string         desc;
        FNHandler           proc    = nullptr;
    };
    
    struct Doc::Repo {
        Map<std::string,Handler*,IgCase>    handlers;
        StringSet                           keys;
    };
    
    Doc::Repo& Doc::repo()
    {
        static Repo s_repo;
        return s_repo;
    }
    

    int              Doc::add_handler(const std::string& key, const std::string& desc, FNHandler proc)
    {
        if(key.empty() || !proc)
            return 0;
            
        Repo&   _r  = repo();
        _r.handlers[key]    = new Handler{ .key=key, .desc=desc, .proc=proc };
        _r.keys << key;
        return (int) _r.handlers.size();
    }
    
    bool Doc::any_terrain(const Obj* obj)
    {
        if(dynamic_cast<const Terrain*>(obj))
            return true;
        if(const Frame* f = dynamic_cast<const Frame*>(obj)){
            return f->children([](const Obj* o2){
                return any_terrain(o2);
            });
        }
        return false;
    }

    const StringSet& Doc::handlers()
    {
        return repo().keys;
    }
    
    Doc::FNHandler   Doc::handler(const std::string&k)
    {
        const Handler*    h = repo().handlers.get(k,nullptr);
        if(!h)  
            return nullptr;
        return h->proc;
    }
    
    bool             Doc::has_handler(const std::string&k)
    {
        const Handler*    h   = repo().handlers.get(k,nullptr);
        return h && h->proc;
    }
    
    std::string      Doc::description(const std::string&k)
    {
        const Handler*    h   = repo().handlers.get(k,nullptr);
        if(!h)
            return {};
        return h->desc;
    }


    ////////////////////////////////////////////////////////////////////////////


    Doc::Doc(const Param& p) : Frame(p), m_args(p.args)
    {
        m_doc = this;
    }
    
    Doc::~Doc()
    {
    }

    void    Doc::calc_points() 
    {
        m_edges  = NAN;
        for(Point*p : m_points){
            if(!p)
                continue;
            Vector2D    pp  = p->global().xy();
            if(is_nan(pp))
                continue;
            if(is_nan(m_edges)){
                m_edges = { pp, pp };
            } else
                m_edges |= pp;
        }
        
        const Terrain* t    = terrain();
        if(t && !is_nan(t->bounds())){
            if(!is_nan(m_edges))
                m_bounds    = m_edges | t->bounds();
            else
                m_bounds    = t->bounds();
        } else
            m_bounds    = m_edges;
    }

    bool    Doc::has_terrain() const
    {
        return any_terrain(this);
    }

    std::filesystem::path   Doc::output_reextension(all_k, std::string_view sfx) const
    {
        return remap_extension(m_file, ALL, sfx);
    }
    
    std::filesystem::path   Doc::output_reextension(last_k, std::string_view  sfx) const
    {
        return remap_extension(m_file, LAST, sfx);
    }
    
    bool    Doc::parse_file(const std::filesystem::path& file)
    {
        b3Error << "Parsing is not yet implemented";
        return false;
    }
}


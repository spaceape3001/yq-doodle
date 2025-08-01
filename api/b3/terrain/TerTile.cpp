////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "TerTile.hpp"
#include <b3/ObjMetaWriter.hpp>
#include <b3/terrain/Terrain.hpp>
#include <b3/terrain/TerPage.hpp>
#include <yq/core/Ref.hpp>
#include <yq/shape/AxBox2.hxx>
#include <yq/vector/Vector2.hxx>

YQ_OBJECT_IMPLEMENT(yq::b3::TerTile)

namespace yq::b3 {
    Obj::Param    TerTile::override_parent(const Param& p, Terrain* t)
    {
        Param   ret(p);
        ret.frame   = t;
        return ret;
    }

    TerTile::TerTile(Terrain*t, const Coord2I&c, const Param&p) : Linear(override_parent(p, t))
    {
        m_coord     = c;
        m_terrain   = t;
        
        if(m_terrain->hydro(HAS))
            m_flags |= F::Hydro;
        if(m_terrain->litho(HAS))
            m_flags |= F::Litho;
        
        m_waterLevel    = m_terrain->water_level();
        m_bounds    = { m_terrain->position(c), m_terrain->position(c + Coord2I{1,1} )};
        set_focus(m_bounds.center().z(0.));
    }
    
    TerTile::~TerTile()
    {
    }

    void    TerTile::group(TileGroup*tg)
    {
        m_group = tg;
    }

    bool    TerTile::hydro(has_k) const
    {
        return m_flags(F::Hydro);
    }
    
    bool    TerTile::litho(has_k) const
    {
        return m_flags(F::Litho);
    }
    

    uint8_t     TerTile::lod(current_k) const
    {
        if(m_current)
            return m_current -> lod();
        return 0;
    }

    void        TerTile::mark_invalid()
    {
        m_flags -= F::Valid;
    }
    
    TerPage*            TerTile::page(uint8_t n)
    {
        return m_pages.get(n);
    }
    
    const TerPage*      TerTile::page(uint8_t n) const
    {
        return m_pages.get(n);
    }

    TerPage*    TerTile::page(create_k, uint8_t n)
    {
        if(n<TerPage::kMinLOD)
            return nullptr;
        if(n>TerPage::kMaxLOD)
            return nullptr;
        if(m_pages.has(n))
            return nullptr;
        
        TerPagePtr    tp  = new TerPage({ .file = m_terrain->calc_filename(m_coord, n),
            .hydro  = m_flags(F::Hydro),
            .litho  = m_flags(F::Litho),
            .lod    = n
        });
        m_pages[n]  = tp;
        return tp;
    }
    
    bool    TerTile::page(erase_k, uint8_t n)
    {
        auto tp = m_pages.get(n);
        if(!tp)
            return false;
        if(tp.ptr() == m_current)
            m_current   = nullptr;
        m_pages.erase(n);
        return true;
    }

    bool    TerTile::page(load_k, uint8_t n)
    {
        if(n<TerPage::kMinLOD)
            return false;
        if(n>TerPage::kMaxLOD)
            return false;
        if(m_pages.has(n))
            return false;
        
        TerPagePtr    tp  = new TerPage({ .file = m_terrain->calc_filename(m_coord, n),
            .hydro  = m_flags(F::Hydro),
            .litho  = m_flags(F::Litho),
            .lod    = n
        });
        if(!tp->load())
            return false;
        m_pages[n]  = tp;
        return true;
    }

    bool    TerTile::page(save_k, uint8_t n)
    {
        auto tp = m_pages.get(n);
        if(!tp)
            return false;
        return tp -> save();
    }

    bool    TerTile::page(set_k, uint8_t n)
    {
        auto tp = m_pages.get(n);
        if(!tp)
            return false;
        m_current   = tp.ptr();
        return true;
    }

    std::pair<const TerPage*, uint8_t>  TerTile::page(similar_k, uint8_t lod) const
    {
        auto tp = m_pages.get(lod);
        if(tp)
            return { tp, lod };
        
        auto i  = m_pages.upper_bound(lod);
        if(i != m_pages.end())
            return { i->second, i->first };
        
        auto j = m_pages.lower_bound(lod);
        if(j != m_pages.end())
            return { j->second, j->first };

        return {nullptr, 0};
    }

    void         TerTile::set_water_level(double v)
    {
        m_flags |= F::Hydro;
        m_waterLevel    = v;
    }
    
    bool         TerTile::valid() const
    {
        return m_flags(F::Valid);
    }
}

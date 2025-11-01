////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/keywords.hpp>
#include <yq/b3/spatial/Linear.hpp>
#include <yq/shape/AxBox2.hpp>

namespace yq::b3 {

    class Terrain;
    class TerPage;
    class TileGroup;

    class TerTile : public Linear {
        YQ_OBJECT_DECLARE(TerTile, Linear)
    public:
        TerTile(Terrain*, const Coord2I&, const Param&p={});
        ~TerTile();
        
        TileGroup*          group() { return m_group; }
        const TileGroup*    group() const { return m_group; }

        void                group(TileGroup*);
        
        const Coord2I&      coord() const { return m_coord; }
        const AxBox2D&      bounds() const { return m_bounds; }

        bool                hydro(has_k) const;
        bool                litho(has_k) const;

        uint8_t             lod(current_k) const;
        void                mark_invalid();

        TerPage*            page(uint8_t);
        const TerPage*      page(uint8_t) const;
        
        //! Create a new LOD (unallocated)
        TerPage*            page(create_k, uint8_t);
        
        //! Erase a LOD (note, will unset the current if it matches)
        bool                page(erase_k, uint8_t);

        //! Load a particular LOD
        bool                page(load_k, uint8_t);
        
        bool                page(save_k, uint8_t);
        
        
        //! Set the current LOD
        bool                page(set_k, uint8_t);
        
        std::pair<const TerPage*, uint8_t>  page(similar_k, uint8_t) const;
        bool                valid() const;
        
        
        
        double              water_level() const { return m_waterLevel; }
        
        void                set_water_level(double);

        enum class F {
            Valid,
            Litho,
            Hydro
        };
        
    private:
        
        static Param    override_parent(const Param&, Terrain*);
      
        AxBox2D                 m_bounds;
        Coord2I                 m_coord;
        Terrain*                m_terrain   = nullptr;
        
        TerPage*                m_current   = nullptr;
        Map<int,TerPagePtr>     m_pages;
        TileGroup*              m_group = nullptr;
        Flags<F,uint32_t>       m_flags;
        double                  m_waterLevel    = NAN;
    };
}

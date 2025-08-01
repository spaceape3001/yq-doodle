////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <b3/Frame.hpp>
#include <yq/container/Array.hpp>
#include <yq/container/Set.hpp>
#include <yq/shape/AxBox2.hpp>
#include <filesystem>

#ifdef NAN
    #undef NAN
#endif

namespace yq::b3 {
    class TerTile;
    class TileGroup;
    
    class Terrain : public Frame {
        YQ_OBJECT_DECLARE(Terrain, Frame)
    public:
        struct CalcResult {
            const TerPage*      page    = nullptr;
            Coord2I             idx     = {};
            Vector2D            frac    = {};
        };

        Terrain(const std::filesystem::path&, const Param&);
        virtual ~Terrain();
        
        const AxBox2D&                  bounds() const { return m_bounds; }
        
        const Vector2D&                 tile_size() const { return m_tileSize; }
        const std::filesystem::path&    directory() const { return m_directory; }
        
        CalcResult                      calc(const Vector2D&, uint8_t lod=0) const;
        std::filesystem::path           calc_filename(const Coord2I&, uint8_t lod) const;
        
        double      water_level() const { return m_waterLevel; }
    
        enum class F : uint8_t {
            Valid,
            Litho,
            Hydro
        };

        double                  litho(const Vector2D&) const;
        double                  hydro(const Vector2D&) const;

        bool                    hydro(has_k) const;
        bool                    litho(has_k) const;
        
        double                  west() const { return m_bounds.lo.x; }
        double                  east() const { return m_bounds.hi.x; }
        double                  south() const { return m_bounds.lo.y; }
        double                  north() const { return m_bounds.hi.y; }
        bool                    is_water(const Vector2D&) const;

        virtual void            frame_pop() override;

        TileGroup*              group(const std::string&);
        const TileGroup*        group(const std::string&) const;

        TerPage*                page(const Coord2I&, uint8_t lod=0);
        TerPage*                page(create_k, const Coord2I&, uint8_t lod=0);
        const TerPage*          page(const Coord2I&, uint8_t lod=0) const;
        

        Vector2D                position(const Coord2I&) const;
        Vector2D                position(int,int) const;

        
        TerTile*                tile(const Coord2I&);
        const TerTile*          tile(const Coord2I&) const;

        TerTile*                tile(int,int);
        const TerTile*          tile(int,int) const;
        
        int                     trow() const { return m_trow; };
        void                    trow(int v) { m_trow = v; }
        
        const auto&             tiles() const { return m_tiles; }

    private:
    
        void    _init();
    
        ZArray2<TerTile*>       m_tiles;
        AxBox2D                 m_bounds    = NAN;
        std::filesystem::path   m_directory;
        Vector2D                m_tileSize  = {1024., 1024.};
        double                  m_waterLevel    = NAN;
        Flags<F,uint32_t>       m_flags;
        Set<uint8_t>            m_lods;
        Coord2I                 m_center{};
        AxBox2I                 m_counts{};
        Vector<uint32_t>        m_seed;
        int                     m_trow = 0;
    };
}

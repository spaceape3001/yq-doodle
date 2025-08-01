////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Terrain.hpp"
#include <b3/logging.hpp>
#include <b3/Frame.hxx>
#include <b3/ObjMetaWriter.hpp>
#include <b3/terrain/TileGroup.hpp>
#include <b3/terrain/TerPage.hpp>
#include <b3/terrain/TerTile.hpp>
#include <b3/util/parse.hpp>
#include <yq/shape/AxBox2.hxx>
#include <cstdio>

YQ_OBJECT_IMPLEMENT(yq::b3::Terrain)

namespace yq::b3 {
    Terrain::Terrain(const std::filesystem::path& f, const Param& p) : Frame(p), m_directory(f)
    { 
        frame() -> m_terrain  = this;
        _init();
        m_trow      = m_tiles.soft_high().j - 1;
    }
    
    Terrain::~Terrain()
    {
    }

    void    Terrain::_init()
    {
        static constexpr const uint8_t kMaxLOD = TerPage::kMaxLOD;
        static constexpr const uint8_t kMinLOD = TerPage::kMinLOD;
    
        std::error_code ec;
        m_flags -= F::Valid;
        if(!std::filesystem::exists(m_directory, ec)){
            b3Warning << "Terrain directory '" << m_directory << "' does not exist.";
            return ;
        }
        
        if(!std::filesystem::is_directory(m_directory, ec)){
            b3Warning << "Terrain path '" << m_directory << "' is not a directory";
            return ;
        }
        
        //  Tile size
        auto ts = attrs().attr("tile");
        if(!ts.empty()){
            if(ts.find_first_of(',')){
                m_tileSize  = parse::vector2(ts);
            } else {
                m_tileSize.x    = m_tileSize.y  = parse::length(ts, 1024.);
            }
        }
        
        // Water
        if(attrs().has("water")){
            m_flags |= F::Hydro;
            m_waterLevel    = attrs().length("water");
        }
        
        m_flags |= F::Litho;

        auto ld = attrs().attr("lod");
        if(!ld.empty()){
            if(ld.find("..") != std::string_view::npos){
                RangeI  ll   = parse::irange(ld);
                ll.lo   = std::clamp(ll.lo, (int) kMinLOD, (int) kMaxLOD);
                ll.hi   = std::clamp(ll.hi, (int) kMinLOD, (int) kMaxLOD);

                if(ll.lo > ll.hi){
                    std::swap(ll.lo, ll.hi);
                } else if(ll.lo == ll.hi)
                    ++ll.hi;
                for(int l=ll.lo;l<ll.hi;++l)
                    m_lods << (uint8_t) l;
            } else if(ld.find_first_of(',')){
                for(int i : parse::integer_set(ld)){
                    if(i<(int) kMinLOD)
                        continue;
                    if(i>(int) kMaxLOD)
                        continue;
                    m_lods << (uint8_t) i;
                }
            } else {
                int l   = parse::integer(ld);
                if((l>=kMinLOD) && (l<=kMaxLOD))
                    m_lods << l;
            }
        }
        
        if(m_lods.empty())
            m_lods << kMinLOD;
            
        uint8_t     lod0    = m_lods.first();
        
        RangeI          rr{}, cc{};
        auto cnts   = attrs().attr("tiles");
        if(cnts.empty()){
            m_counts    = AxBox2I( {0,0}, {1,1});
        } else if(auto n = cnts.find(','); n != std::string_view::npos){
            
            std::string_view    c   = cnts.substr(0,n);
            if(c.find("..") != std::string_view::npos){
                cc  = parse::irange(c, {0,1});
            } else {
                cc  = { 0, std::min(1,parse::integer(c, 1)) };
            }

            std::string_view    r   = cnts.substr(n+1);
            if(r.find("..") != std::string_view::npos){
                rr  = parse::irange(r, {0,1});
            } else {
                rr  = { 0, std::min(1,parse::integer(r, 1))};
            }
            
        } else {
            if(cnts.find("..") != std::string_view::npos){
                rr = cc = parse::irange(cnts, {0,1});
            } else {
                rr = cc = { 0, std::min(1,parse::integer(cnts, 1))};
            }
        }
        
        if(rr.lo > rr.hi){
            std::swap(rr.lo, rr.hi);
        } else if(rr.hi == rr.lo)
            ++rr.hi;
        
        if(cc.lo > cc.hi){
            std::swap(cc.lo, cc.hi);
        } else if(cc.hi == cc.lo)
            ++cc.hi;
        
        m_counts    = { { cc.lo, rr.lo }, { cc.hi, rr.hi }};
        m_center    = attrs().coord2("center");
        
        
        Coord2I     lo{ cc.lo, rr.lo };
        Coord2I     hi{ cc.hi, rr.hi };

        m_trow      = rr.hi;

        m_tiles.resize(lo, hi);
        for(int i=cc.lo;i<cc.hi;++i)
            for(int j=rr.lo;j<rr.hi;++j) {
            TerTile*    tt  = new TerTile(this, {i,j});
            m_tiles(i,j)  = tt;
            tt -> page(CREATE, lod0);
        }
        
        m_bounds    = m_tiles({cc.lo, rr.lo}) -> bounds();
        for(auto& t : m_tiles)
            m_bounds |= t->bounds();
    }

    Terrain::CalcResult  Terrain::calc(const Vector2D&, uint8_t lod) const
    {
        CalcResult  ret;
        
        return {};
    }

    std::filesystem::path   Terrain::calc_filename(const Coord2I& c, uint8_t lod) const
    {
        char buffer[256];
        sprintf(buffer, "ipz%+02d%+02dr%02d.b3ter", c.i, c.j, (int) lod);
        
        if(m_directory.empty())
            return buffer;
        return m_directory / buffer;
    }

    void            Terrain::frame_pop() 
    {
        for(auto& t : m_tiles){
            if(!t)
                continue;
            for(uint8_t lod : m_lods)
                t->page(CREATE, lod);
        }
        Frame::frame_pop();
    }


    TileGroup*              Terrain::group(const std::string&k)
    {
        if(TileGroup*  tg  = child_as<TileGroup>(k))
            return tg;
        return frame() -> child_as<TileGroup>(k);
    }
    
    const TileGroup*        Terrain::group(const std::string&k) const
    {
        if(const TileGroup*  tg  = child_as<TileGroup>(k))
            return tg;
        return frame() -> child_as<TileGroup>(k);
    }


    bool                    Terrain::hydro(has_k) const
    {
        return m_flags(F::Hydro);
    }
    
    bool                    Terrain::litho(has_k) const
    {
        return m_flags(F::Litho);
    }

    Vector2D                Terrain::position(const Coord2I&c) const
    {
        return position(c.i,c.j);
    }

    Vector2D                Terrain::position(int i,int j) const
    {
        return { m_tileSize.x * i, m_tileSize.y * j };
    }

    TerTile*                Terrain::tile(const Coord2I&c)
    {
        if(!m_tiles.is_interior(c))
            return nullptr;
        return m_tiles(c);
    }
    
    const TerTile*          Terrain::tile(const Coord2I&c) const
    {
        if(!m_tiles.is_interior(c))
            return nullptr;
        return m_tiles(c);
    }

    TerTile*                Terrain::tile(int i,int j)
    {
        return tile({i,j});
    }
    
    const TerTile*          Terrain::tile(int i,int j) const
    {
        return tile({i,j});
    }
}

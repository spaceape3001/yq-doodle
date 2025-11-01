////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Terrain.hpp"
#include <yq/b3/logging.hpp>
#include <yq/b3/Frame.hxx>
#include <yq/b3/ObjMetaWriter.hpp>
#include <yq/b3/terrain/TileGroup.hpp>
#include <yq/b3/terrain/TerPage.hpp>
#include <yq/b3/terrain/TerTile.hpp>
#include <yq/b3/util/parse.hpp>
#include <yq/text/join.hpp>

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
            if(ts.find_first_of(',') != std::string_view::npos) {
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
            
        auto ctr    = attrs().coord2("center");

        uint8_t     lod0    = m_lods.first();
        
        RangeI          rr{}, cc{};
        auto cnts   = attrs().attr("tiles");
        if(cnts.empty()){
            m_coords    = AxBox2I( {0,0}, {1,1});
        } else if(auto n = cnts.find(','); n != std::string_view::npos){
            std::string_view    c   = cnts.substr(0,n);
            if(c.find("..") != std::string_view::npos){
                cc  = parse::irange(c, {0,1});
            } else {
                cc  = { 0, std::max(1,parse::integer(c, 1)) };
            }

            std::string_view    r   = cnts.substr(n+1);
            if(r.find("..") != std::string_view::npos){
                rr  = parse::irange(r, {0,1});
            } else {
                rr  = { 0, std::max(1,parse::integer(r, 1))};
            }
            
        } else {
            if(cnts.find("..") != std::string_view::npos){
                rr = cc = parse::irange(cnts, {0,1});
            } else {
                rr = cc = { 0, std::max(1,parse::integer(cnts, 1))};
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
        
        m_coords    = { { cc.lo - ctr.i, rr.lo - ctr.j }, { cc.hi - ctr.i, rr.hi -  ctr.j }};
        
        
        Coord2I     lo{ m_coords.lo.x, m_coords.lo.y };
        Coord2I     hi{ m_coords.hi.x+1, m_coords.hi.y+1 };
        m_trow      = m_coords.hi.y+1;

        m_tiles.resize(lo, hi);
        
        for(int i=lo.i;i<hi.i;++i)
            for(int j=lo.j;j<hi.j;++j) {
            
            std::string     tname    = std::format("tile@{},{}", i, j);
            TerTile*    tt  = new TerTile(this, {i,j}, { .name=tname });
            m_tiles(i,j)  = tt;
            tt -> page(CREATE, lod0);
        }
        
        m_bounds    = m_tiles({cc.lo, rr.lo}) -> bounds();
        for(auto& t : m_tiles)
            m_bounds |= t->bounds();
    }

    Terrain::CalcResult  Terrain::calc(const Vector2D& pos, uint8_t lod) const
    {
        CalcResult  ret;
        
        Vector2D    tcr  = pos.ediv(m_tileSize);
        Vector2I    tci  = iround(tcr);
        Vector2I    tidx = tci.emin(m_coords.lo).emax(m_coords.hi);
        tcr             += (tci - tidx).cast<double>();  // now in fractions of a tile
        
        const TerTile*  tt  = tile(tidx.x, tidx.y);
        if(!tt)
            return ret;
    
        auto [tp, n]    = tt->page(SIMILAR, lod);
        if(!tp)
            return ret;
        lod     = n;
        ret.page        = tp;
    
        double      sz  = (double)(1<<lod);
        int         mx  = 1 << lod;
        
        auto apply = [&](double c, unsigned&i, float& f){
            if(c < 0.){
                i       = 0;
                f       = (float)(c * sz);
            } else if(c > 1.){
                i       = (unsigned) mx;
                f       = (float)((c-1.) * sz);
            } else {
                i       = (unsigned) (c*sz);
                f       = (float)(sz*c - (double) i);
            }
        };

        apply(tcr.x, ret.idx.i, ret.frac.i);
        apply(tcr.y, ret.idx.j, ret.frac.j);

        return ret;
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

    double                  Terrain::hydro(const Vector2D&v) const
    {
        auto cc = calc(v);
        if(!cc.page)
            return NAN;
        if(!cc.page->has_hydro())
            return NAN;
        return cc.page->hydro().linear(cc.idx, cc.frac);
    }

    bool                    Terrain::hydro(has_k) const
    {
        return m_flags(F::Hydro);
    }
    
    bool                    Terrain::is_water(const Vector2D&v) const
    {
        double  h   = hydro(v);
        double  l   = litho(v);
        if(is_nan(h)){
            return false;
        } else if(is_nan(l)){
            return true;
        } else {
            return h > l;
        }
    }

    double                  Terrain::litho(const Vector2D&v) const
    {
        auto cc = calc(v);
        if(!cc.page)
            return NAN;
        if(!cc.page->has_litho())
            return NAN;
        return cc.page->litho().linear(cc.idx, cc.frac);
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
        if(!m_coords.contains({c.i, c.j}))
            return nullptr;
        return m_tiles(c);
    }
    
    const TerTile*          Terrain::tile(const Coord2I&c) const
    {
        if(!m_coords.contains({c.i, c.j}))
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

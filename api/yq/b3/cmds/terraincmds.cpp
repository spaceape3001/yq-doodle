////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/b3/logging.hpp>
#include <yq/b3/Parser.hpp>
#include <yq/b3/terrain/StdTerrain.hpp>
#include <yq/b3/terrain/TerTile.hpp>
#include <yq/b3/terrain/TileGroup.hpp>
#include <yq/file/DirUtils.hpp>
#include <yq/file/FileUtils.hpp>

using namespace yq;
using namespace yq::b3;

static bool cmdTerrain(Parser& p, const ArgList&, const ArgMap&);

////////////////////////////////////////////////////////////////////////////////

static bool cmdTagTerrain(Parser& p, const ArgList& pArgs, const ArgMap& nArgs)
{
    ArgMap subArgs = nArgs;
    subArgs.attrs["$ter"] = "true";
    return p.execute(pArgs, subArgs);
}
YQ_B3_COMMAND("ter", ifSubcommand, 0, cmdTagTerrain);

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
static bool cmdTerrain(Parser& p, const ArgList&pArgs, const ArgMap&nArgs) 
{
    std::string             arg = pArgs.string(0);
    std::filesystem::path   pth(arg);
    if(pth.empty()){
        pth = p.file().parent_path() / ".tcache";
    } else if(pth.is_relative()){
        auto p2 = p.file().parent_path() / arg;
        if(file_exists(p2)){
            pth = p2;
        } else {
            pth = p.cache() / p.file().filename() / arg;
            make_path(pth);
        }
    } 

    p << new StdTerrain(pth, {.args=pArgs, .attrs=nArgs, .frame=p.frame()});
    return true;
}
YQ_B3_COMMAND("terrain", ifNone, 1, cmdTerrain);

////////////////////////////////////////////////////////////////////////////////

static bool cmdTileGroup(Parser& p, const ArgList& pArgs, const ArgMap& nArgs)
{
    //Terrain*    pter   = dynamic_cast<Terrain*>(p.frame());
    //if(!pter){
        //p.gripe("Terrain ONLY!");
        //return false;
    //}
    
    p << new TileGroup({.attrs=nArgs, .frame=p.frame(), .name=pArgs.string(0)});
    return true;
}
YQ_B3_COMMAND("tgroup", ifNone, 1, cmdTileGroup);


////////////////////////////////////////////////////////////////////////////////

static bool cmdTile(Parser& p, const ArgList&pArgs, const ArgMap&nArgs) 
{
    TileGroup*  tg      = dynamic_cast<TileGroup*>(p.frame());
    Terrain*    pter    = dynamic_cast<Terrain*>(p.frame());
    if(!pter && !tg){
        p.gripe("Terrain ONLY!");
        return false;
    }
    if(tg)
        pter = static_cast<Terrain*>(tg->frame());
    
    Coord2     tc  = pArgs.coord2(0);
    TerTile*  t   = pter->tile(tc);
    if(!t){
        b3Info << "Failed to find tile " << tc.i << " " << tc.j << "\n";
        p.gripe("Valid tile required!");
        return false;
    }

    if(tg)
        t->merge(tg->attrs());
    t->merge(nArgs);
    //if(nArgs.has("lod"))
    //    t.setLOD(nArgs.intset("lod"));
    if(t->attrs().boolean("invalid"))
        t->mark_invalid();
    if(t->attrs().has("water"))
        t->set_water_level(nArgs.length("water", 0.));
    p << t;
    return true;
}
YQ_B3_COMMAND("tile", ifNone, 1, cmdTile);

////////////////////////////////////////////////////////////////////////////////

static bool cmdTileRow(Parser& p, const ArgList& pArgs, const ArgMap& nArgs)
{
    Terrain*    pter    = dynamic_cast<Terrain*>(p.frame());
    if(!pter){
        p.gripe("Terrain ONLY!");
        return false;
    }

    int row = nArgs.integer("r", pter->trow());
    pter->trow(row-1);
    int col = nArgs.integer("c", pter->tiles().soft_low().i);
    int cmax    = pter->tiles().soft_high().i;

    for(const std::string& s : pArgs.values){
        if(col >= cmax)
            break;
            
        TerTile*   t   = pter->tile(col, row);
        ++col;
        
        TileGroup*  tg  = pter->group(s);
        if(tg && t){
            t->merge(tg->attrs(), true);
            t->group(tg);
        } else {
            p.gripe("Bad tile/group " + s);
            
            //for(QString s : pter->byName.keys())
            //    std::cout << "child " << s << "\n";
        }
    }
    return true;
}
YQ_B3_COMMAND("trow", ifNone, 1, cmdTileRow);

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "b3.hpp"
#include <yq/b3/spatial/Point.hpp>
#include <yq/b3/spatial/PointLine.hpp>
#include <yq/b3/terrain/Terrain.hpp>

#include <yq/b3/Frame.hxx>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

static bool    includedFiles(Doc& doc)
{
    for(auto& fp : doc.files())
        std::cout << fp.string() << "\n";
    return true;
}

YQ_B3_HANDLER("files", "List files used during parse", includedFiles)

////////////////////////////////////////////////////////////////////////////////

static bool     nullNothing(Doc&doc)
{
    return true;
}

YQ_B3_HANDLER("null", "Does nothing (used for parsing checks)", nullNothing)

////////////////////////////////////////////////////////////////////////////////

static bool    objCounter(Doc&)
{
    std::cout << "Obj allocations is " << Obj::net_allocations();
    return true;
}

YQ_B3_HANDLER("objcnt", "Net number of objects created", objCounter)


////////////////////////////////////////////////////////////////////////////////

static void     writeTree(const Obj& obj, unsigned depth=0)
{
    for(unsigned n=1;n<depth;++n)
        std::cout << "  ";
    if(depth)
        std::cout << "> ";
    
    std::cout << obj.metaInfo().stem() << " {" << obj.name() << "}";
    
    if(const Point* pt = dynamic_cast<const Point*>(&obj)){
        std::cout << " {" << pt->define().x << ", " << pt->define().y << ", " << key_for(pt->type()) << " " << pt->define().z << "}";
    }

    if(const Terrain* t = dynamic_cast<const Terrain*>(&obj)){
        
    }
    
    if(const PointLine* pl = dynamic_cast<const PointLine*>(&obj)){
        std::cout << " (" << pl->points(COUNT) << " points)";
    }
    
    std::cout << '\n';
    
    if(const Frame* pt = dynamic_cast<const Frame*>(&obj)){
        pt->children([&](const Obj& ch){
            writeTree(ch, depth+1);
        });
    }
}

static bool     objectTree(Doc& doc)
{
    writeTree(doc);
    return true;
}

YQ_B3_HANDLER("objtree", "Objects (tree hierarchy)", objectTree)

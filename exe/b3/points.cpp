////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "b3.hpp"

#include <b3/spatial/Point.hpp>
#include <yq/container/Array.hpp>
#include <yq/text/format.hpp>
#include <array>
#include <iostream>


using namespace yq;
using namespace yq::b3;



static bool docPointsTable(Doc& doc)
{
    auto& pts    = doc.points();
    
    //  columns....
    //  N, Name, DX, DY, PT, DZ, GX, GY, GZ
    
    enum : unsigned {
        ColIdx,
        ColName,
        ColDefX,
        ColDefY,
        ColPtType,
        ColDefZ,
        ColGlobalX,
        ColGlobalY,
        ColGlobalZ,
        COLUMNS
    };
    
    std::string_view    kColumns[] = {
        "n",
        "name",
        "Local X",
        "Local Y",
        "Type",
        "Local Z",
        "Global X",
        "Global Y",
        "Global Z",
    };
    
    bool                rightCols[] = {
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false
    };
    
    
    Array2<std::string>             display;
    std::array<size_t,COLUMNS>      colmax{};
    
    for(unsigned c = 0; c<COLUMNS; ++c)
        colmax[c] = kColumns[c].size();
    
    display.resize({ (unsigned) pts.size(), COLUMNS });
    unsigned          n   = 0;
    for(const Point* pt : pts){
        if(!pt){
            ++n;
            continue;
        }
        
        display({n, ColIdx})    = std::format("{}", n);
        
        std::string             fn  = pt->full_name();
        if(fn.empty())
            fn      = std::string(pt->name());
        display({n, ColName})   = std::move(fn);
        
        display({n, ColDefX})       = std::format("{}", pt->define().x );
        display({n, ColDefY})       = std::format("{}", pt->define().y );
        display({n, ColDefZ})       = std::format("{}", pt->define().z );
        
        display({n, ColPtType})     = std::string(key_for(pt->type()));
        display({n, ColGlobalX})    = std::format("{}", pt->global().x );
        display({n, ColGlobalY})    = std::format("{}", pt->global().y );
        display({n, ColGlobalZ})    = std::format("{}", pt->global().z );
        
        for(unsigned c = 0; c<COLUMNS;++c)
            colmax[c]   = std::max(colmax[c], display({n,c}).size());
        ++n;
    }
    
    for(unsigned c = 0; c < COLUMNS; ++c){
        std::cout << "| ";
        std::cout.width(colmax[c]);
        std::cout.setf(std::ios::left);
        std::cout << kColumns[c];
        std::cout.width(0);
        std::cout << ' ';
    }
    
    std::cout << "|\n";
    for(unsigned c = 0; c < COLUMNS; ++c){
        std::cout << '+';
        for(unsigned i = 0; i<colmax[c]+2; ++i)
            std::cout << '=';
    }
    std::cout << "+\n";
    
    for(unsigned r = 0; r < n; ++r){
        for(unsigned c = 0; c<COLUMNS; ++c){
            std::cout << "| ";
            std::cout.width(colmax[c]);
            if(rightCols[c]){
                std::cout.setf(std::ios::right);
            } else {
                std::cout.setf(std::ios::left);
            }
            std::cout << display(r,c);
            std::cout.width(0);
            std::cout << ' ';
        }
        std::cout << " |\n";
    }
    std::cout << '\n';
    
    return true;
}


YQ_B3_HANDLER("points", "Prints the points table", docPointsTable);



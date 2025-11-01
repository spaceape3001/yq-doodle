////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <art/doc/Doc.hpp>
#include <artVk/ArtDocPtr.hpp>
#include <tachyon/api/Tachyon.hpp>

namespace yq::art {

    //! Used to maintain document/scenes
    class Keeper : public tachyon::Tachyon, public ArtDocPtr {
        YQ_TACHYON_DECLARE(Keeper, tachyon::Tachyon)
    public:
        Keeper(const DocPtr&);
        ~Keeper();
        
    private:
        
    };
}

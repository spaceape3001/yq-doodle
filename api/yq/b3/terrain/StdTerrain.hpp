////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/terrain/Terrain.hpp>

namespace yq::b3 {
    class  StdTerrain : public Terrain {
        YQ_OBJECT_DECLARE(StdTerrain, Terrain)
    public:
        StdTerrain(const std::filesystem::path&, const Param&);
        ~StdTerrain();
    };
}

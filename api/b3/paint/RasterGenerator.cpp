////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "RasterGenerator.hpp"
#include <yq/errors.hpp>

namespace yq::b3 {
    RasterGenerator::RasterGenerator()
    {
    }
    
    RasterGenerator::~RasterGenerator()
    {
    }
        
    std::error_code     RasterGenerator::save_to(const std::filesystem::path&) const
    {
        return errors::todo();  // NYI
    }
}


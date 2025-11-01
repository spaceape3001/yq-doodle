////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/paint/PaintDevice.hpp>
#include <filesystem>
#include <system_error>

namespace yq::b3 {
    class RasterGenerator : public PaintDevice {
    public:
    
        RasterGenerator();
        virtual ~RasterGenerator();
        
        std::error_code     save_to(const std::filesystem::path&) const;
        virtual bool        pixelated() const override { return true; }
        
    private:
        
    };
}

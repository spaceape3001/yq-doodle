////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Light.hpp"
#include "LightInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::doodle::Light)

namespace yq::doodle {
    LightInfo::LightInfo(std::string_view zName, DObjectInfo& base, const std::source_location& sl) : DObjectInfo(zName, base, sl)
    {
        set(Flag::LIGHT);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    void Light::init_info()
    {
        auto w = writer<Light>();
        w.description("Light");
    }

    Light::Light(Project& prj) : DObject(prj)
    {
    }
    
    Light::Light(CopyAPI& api, const Light& cp) : DObject(api, cp)
    {
    }
    
    Light::~Light()
    {
    }



    //! Remap IDs/pointers appropriately
    void        Light::remap(const Remapper&rMap)
    {
        DObject::remap(rMap);
    }
}


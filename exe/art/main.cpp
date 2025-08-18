////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ArtApp.hpp"
#include "ArtMW.hpp"
#include <tachyon/api/Tachyon.hxx>

int main(int argc, char* argv[])
{
    configure_standand_resource_path();

    AppCreateInfo        aci;
    aci.thread.sim        = true;
    aci.view.title        = "Art";
    aci.view.resizable    = false;
    aci.view.size         = { 1920, 1080 };
    aci.view.clear        = { 0.01f, 0.01f, 0.01f, 1.0f };
    aci.view.imgui        = true;

    ArtApp   app(argc, argv, aci);
    app.start();
    
    ArtMW*   mw  = Widget::create<ArtMW>();
    app.run(mw);
    return 0;
}

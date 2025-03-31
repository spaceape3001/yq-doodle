////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DoodleApp.hpp"
#include "DoodleMW.hpp"

int main(int argc, char* argv[])
{
    AppCreateInfo        aci;
    aci.thread.sim        = true;
    aci.view.title        = "Doodler";
    aci.view.resizable    = false;
    aci.view.size         = { 1920, 1080 };
    aci.view.clear        = { 0.01f, 0.01f, 0.01f, 1.0f };
    aci.view.imgui        = true;

    DoodleApp   app(argc, argv, aci);
    app.start();
    
    DoodleMW*   mw  = Widget::create<DoodleMW>();
    app.run(mw);
    return 0;
}

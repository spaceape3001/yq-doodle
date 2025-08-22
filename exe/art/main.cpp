////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ArtApp.hpp"
#include "ArtMW.hpp"
#include <art/doc/Canvas.hpp>
#include <tachyon/api/Tachyon.hxx>

int main(int argc, char* argv[])
{
    configure_standand_resource_path();

    AppCreateInfo        aci;
    aci.thread.sim        = true;
    aci.thread.viewer     = true;
    aci.view.title        = "Art";
    aci.view.resizable    = false;
    aci.view.size         = { 1920, 1080 };
    aci.view.clear        = { 0.01f, 0.01f, 0.01f, 1.0f };
    aci.view.imgui        = true;

    ArtApp   app(argc, argv, aci);
    app.start();

    std::vector<WidgetPtr>    starters;
    
    for(int i=1;i<argc;++i){
        std::error_code ec;
        std::filesystem::path   pth(argv[i]);
        if(!std::filesystem::exists(pth, ec))
            continue;
        
        DocPtr  doc = Doc::load_xml(pth);
        if(!doc)
            continue;
        starters.push_back(Widget::create<ArtMW>(doc));
    }
    
    if(starters.empty())
        starters.push_back(Widget::create<ArtMW>(new Canvas));
    app.run(starters);
    return 0;
}

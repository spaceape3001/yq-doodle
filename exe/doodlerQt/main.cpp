////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <yq/process/PluginLoader.hpp>
#include "DoodleApp.hpp"
#include "DoodleMain.hpp"
#include <gluon/core/Logging.hpp>
#include <yq/meta/Meta.hpp>

using namespace yq;

int main(int argc, char* argv[])
{
    DoodleApp   app(argc, argv);
    
    Meta::init();
    load_plugin_dir("plugin/doodle");
    Meta::init();
    load_plugin_dir("plugin/doodleQt");
    
    //  May need a sub-initialization-check for plugins...
    
    Meta::freeze();
    
    if(argc>1){
        bool    any = false;
        for(int i=1;i<argc;++i){
            ProjectQPtr ptr     = ProjectQ::load(argv[i]);
            if(ptr){
                any = true;
                DoodleMain* mw  = new DoodleMain(ptr);
                mw -> show();
            }
        }
        if(!any)
            return 0;
    } else {
        DoodleMain* mw  = new DoodleMain;
        mw -> show();
    }

    return app.exec();
}

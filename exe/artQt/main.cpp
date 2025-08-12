////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <art/logging.hpp>

#include "ArtApp.hpp"
#include "ArtMain.hpp"


#include <art/doc/Canvas.hpp>
#include <artQt/canvas/CanvasQ.hpp>
#include <yq/meta/Meta.hpp>
#include <yq/process/PluginLoader.hpp>

#include <iostream>

using namespace yq;
using namespace yq::art;


DocumentQPtr        defaultDocument()
{
    return new CanvasQ(new Canvas);
}

int main(int argc, char* argv[])
{
    ArtApp   app(argc, argv);
    
    Meta::init();
    load_plugin_dir("plugin/art");
    Meta::init();
    load_plugin_dir("plugin/artQt");
    
    //  May need a sub-initialization-check for plugins...
    
    yq::Meta::freeze();

    if(argc>1){
        bool    any = false;
        for(int i=1;i<argc;++i){
            DocumentQPtr ptr     = DocumentQ::load(argv[i]);
            if(ptr){
                any = true;
                ArtMain* mw  = new ArtMain(ptr);
                mw -> show();
            }
        }
        if(!any)
            return 0;
    } else {
        ArtMain* mw  = new ArtMain;
        mw -> show();
    }

    return app.exec();
}

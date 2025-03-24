////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DoodleApp.hpp"

using namespace yq;
using namespace yq::gluon;

int     DoodleApp::s_mainCount    = 0;

void    DoodleApp::increment()
{
    ++s_mainCount;
}

void    DoodleApp::decrement()
{
    if(--s_mainCount <= 0)
        app()->quit();
}

DoodleApp::DoodleApp(int& argc, char** argv) : Application(argc, argv)
{
}

DoodleApp::~DoodleApp()
{
}



#include "moc_DoodleApp.cpp"

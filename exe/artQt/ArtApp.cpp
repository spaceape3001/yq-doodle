////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ArtApp.hpp"

int     ArtApp::s_mainCount    = 0;

void    ArtApp::increment()
{
    ++s_mainCount;
}

void    ArtApp::decrement()
{
    if(--s_mainCount <= 0)
        app()->quit();
}

ArtApp::ArtApp(int& argc, char** argv) : Application(argc, argv)
{
}

ArtApp::~ArtApp()
{
}



#include "moc_ArtApp.cpp"

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/app/Application.hpp>

class ArtApp : public yq::gluon::Application {
    Q_OBJECT
public:
    ArtApp(int&, char**);
    ~ArtApp();
    
    static void    increment();
    static void    decrement();
    
private:
    
    static int      s_mainCount;
};

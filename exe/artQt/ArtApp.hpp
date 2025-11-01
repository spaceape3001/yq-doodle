////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/app/Application.hpp>


using namespace yq;
//using namespace yq::art;
using namespace yq::gluon;

class ArtApp : public Application {
    Q_OBJECT
public:
    ArtApp(int&, char**);
    ~ArtApp();
    
    static void    increment();
    static void    decrement();
    
private:
    
    static int      s_mainCount;
};

////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/app/Application.hpp>

using namespace yq;
using namespace yq::gluon;


class DoodleApp : public Application {
    Q_OBJECT
public:
    DoodleApp(int&, char**);
    ~DoodleApp();
    
    static void    increment();
    static void    decrement();
    
private:
    
    static int      s_mainCount;
};

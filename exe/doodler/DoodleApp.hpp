////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <tachyon/app/Application.hpp>

using namespace yq;
using namespace yq::tachyon;

class DoodleApp : public Application {
public:
    DoodleApp(int argc, char* argv[], const AppCreateInfo& aci);
    ~DoodleApp();
};

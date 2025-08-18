////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <tachyon/api/Widget.hpp>
#include <art/forward.hpp>
#include <artVk/ArtDocPtr.hpp>

using namespace yq;
using namespace yq::art;
using namespace yq::tachyon;

class ArtMW : public Widget, public ArtDocPtr {
    YQ_TACHYON_DECLARE(ArtMW, Widget)
public:
    ArtMW();
    ArtMW(DocPtr);
    ~ArtMW();
    
    static void init_meta();
    
    void        imgui(ViContext&) override;
    
    void        bar();
    
    void        btn_left();
    void        btn_right();

    void        new_drawing();
};

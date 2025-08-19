////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <tachyon/api/Widget.hpp>
#include <art/forward.hpp>
#include <art/keywords.hpp>
#include <artVk/ArtDocPtr.hpp>

using namespace yq;
using namespace yq::art;
using namespace yq::tachyon;

class ArtMW : public Widget, public ArtDocPtr {
    YQ_TACHYON_DECLARE(ArtMW, Widget)
public:
    ArtMW(DocPtr);
    ~ArtMW();
    
    static void init_meta();
    
    void        imgui(ViContext&) override;
    
    void        bar();
    
    void        btn_left();
    void        btn_right();

    void        new_drawing();

    enum class FileMode {
        None,
        Open,
        Save,
        Copy
    };

    void        cmd_open();
    void        cmd_save();
    void        cmd_save_as();
    void        cmd_save_copy();
    
    void        edit_title();

private:
    FileMode    m_fileMode  = FileMode::None;
    
    void    _update(title_k);
    void    _copy(const std::filesystem::path&);
    void    _open(const std::filesystem::path&);
    void    _save(const std::filesystem::path&);
};

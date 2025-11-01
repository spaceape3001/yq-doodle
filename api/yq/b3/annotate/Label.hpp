////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/b3/Obj.hpp>

namespace yq::b3 {

    class Label : public Obj {
        YQ_OBJECT_DECLARE(Label, Obj)
    public:
        Label(const Param&);
        ~Label();
    
        const std::string& message() const { return m_message; }
    
        const Vector2D&     position() const { return m_position; }
    
    private:
        Vector2D    m_position;
        std::string m_message;
    };
}

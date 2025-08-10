////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/core/WidgetQMetaWriter.hpp>
#include "DocEditor.hpp"

template <typename C>
class DocEditorMeta::Writer : public gluon::WidgetQMeta::Writer<C> {
public:
    Writer(DocEditorMeta* dInfo) : gluon::WidgetQMeta::Writer<C>(dInfo), m_meta(dInfo)
    {
    }
    
    Writer(DocEditorMeta& dInfo) : Writer(&dInfo)
    {
    }

private:
    DocEditorMeta*    m_meta;
};

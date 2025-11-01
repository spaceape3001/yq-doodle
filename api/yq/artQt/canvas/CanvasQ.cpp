////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "CanvasQ.hpp"
#include <yq/artQt/DocumentQMetaWriter.hpp>

YQ_OBJECTQ_IMPLEMENT(yq::art::CanvasQ)

namespace yq::art {

    void CanvasQ::init_meta()
    {
        auto w = writer<CanvasQ>();
        w.description("ArtQt's Canvas");
    }

    CanvasQ::CanvasQ(QObject*parent) : CanvasQ(new Canvas, parent) 
    {
    }
    
    CanvasQ::CanvasQ(Ref<Canvas> doc, QObject*parent) : DocumentQ(doc, parent), m_canvas(doc)
    {
    }
    
    CanvasQ::~CanvasQ()
    {
    }
    
}

#include "moc_CanvasQ.cpp"

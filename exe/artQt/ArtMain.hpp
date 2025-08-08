////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/app/UndoMainWindow.hpp>
#include <artQt/DocumentQ.hpp>

using namespace yq;
using namespace yq::art;
using namespace yq::gluon;


class ArtMain : public UndoMainWindow {
    Q_OBJECT
public:
    ArtMain();
    ArtMain(DocumentQPtr);
    ~ArtMain();

    virtual MainWindow*        newMain() override;
    
public slots:
    //void            cmdNew();
    void            cmdOpen();
    void            cmdSave();
    void            cmdSaveAs();
    void            cmdSaveCopy();
    
protected:
    DocumentQPtr    m_doc;
    
private:
    unsigned        m_number;
    void    updateTitle();
    
    QString         getNewSaveFilename();
};

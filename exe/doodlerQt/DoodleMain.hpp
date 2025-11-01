////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/app/UndoMainWindow.hpp>
#include <yq/doodleQt/ProjectQ.hpp>

using namespace yq;
using namespace yq::gluon;
using namespace yq::doodle;

class DoodleMain : public UndoMainWindow {
    Q_OBJECT
public:
    DoodleMain();
    DoodleMain(ProjectQPtr);
    ~DoodleMain();

    virtual MainWindow*        newMain() override;
    
public slots:
    void            cmdNew();
    void            cmdOpen();
    void            cmdSave();
    void            cmdSaveAs();
    void            cmdSaveCopy();
    void            cmdNewDrawing();
    
private:
    ProjectQPtr     m_project;
    unsigned        m_number;

    void    updateTitle();
    
    QString         getNewSaveFilename();
};

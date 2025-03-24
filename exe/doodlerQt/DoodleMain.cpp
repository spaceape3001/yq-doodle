////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "DoodleMain.hpp"
#include "DoodleApp.hpp"
#include <QMenuBar>
#include <QFileDialog>

DoodleMain::DoodleMain() : DoodleMain(new ProjectQ)
{
}

DoodleMain::DoodleMain(ProjectQPtr prj) : UndoMainWindow(), 
    m_project(prj), m_number(prj->takeANumber())
{
    DoodleApp::increment();
    prj->incrementEditors();
    
    resize(1920, 1080);

    updateTitle();
    connect(prj.ptr(), &ProjectQ::titleChanged, this, &DoodleMain::updateTitle);
    connect(prj.ptr(), &ProjectQ::fileChanged, this, &DoodleMain::updateTitle);

    addAction("copy", "Copy").shortcut(QKeySequence::Copy);
    addAction("cut", "Cut").shortcut(QKeySequence::Cut);
    addAction("paste", "Paste").shortcut(QKeySequence::Paste);
    addAction("delete", "Delete").shortcut(QKeySequence::Delete);
    addAction("new", "New").shortcut(QKeySequence::New).connect(this, &DoodleMain::cmdNew);
    addAction("open", "Open").shortcut(QKeySequence::New).connect(this, &DoodleMain::cmdOpen);
    addAction("save", "Save").shortcut(QKeySequence::Save).connect(this, &DoodleMain::cmdSave);
    addAction("saveas", "Save As").shortcut(QKeySequence::SaveAs).connect(this, &DoodleMain::cmdSaveAs);

    QMenu* fileMenu     = makeMenu("file", "File");
    QMenu* editMenu     = makeMenu("edit", "Edit");
    QMenu* viewMenu     = makeMenu("view", "View");
    QMenu* windowMenu   = makeMenu("window", "Window");
    QMenu* helpMenu     = makeMenu("help", "Help");

    menuBar()->addSeparator();
    QMenu* debugMenu    = makeMenu("debug", "Debug");

    addToMenu(fileMenu,
        QStringList() 
            << "new"
            << "open"
            << "save"
            << "saveas"
    );

    addToMenu(editMenu,
        QStringList() 
            << "undo"
            << "redo"
            << "--"
            << "cut"
            << "copy"
            << "paste"
            << "delete"
    );

    addToMenu(viewMenu,
        QStringList()
    );

    addToMenu(windowMenu,
        QStringList()
    );
    
    addToMenu(helpMenu,
        QStringList()
    );
    
    addToMenu(debugMenu,
        QStringList()
    );
    
    enableDetachableTabs();
    enableAutoEnableCmds();
    enableClosableTabs();
}

DoodleMain::~DoodleMain()
{
    DoodleApp::decrement();
    m_project->decrementEditors();
}

void    DoodleMain::cmdNew()
{
    
}

void    DoodleMain::cmdOpen()
{
}

void    DoodleMain::cmdSave()
{
    if(m_project->filename().isEmpty()){
        cmdSaveAs();
    } else {
        m_project->save();
        updateTitle();
    }
}

void    DoodleMain::cmdSaveAs()
{
    QString file    = getNewSaveFilename();
    if(file.isEmpty())
        return ;
    m_project->saveAs(file);
    updateTitle();
}

void    DoodleMain::cmdSaveCopy()
{
    QString file    = getNewSaveFilename();
    if(file.isEmpty())
        return ;
    m_project->saveTo(file);
}

QString         DoodleMain::getNewSaveFilename()
{
    QString     curFile = m_project->filename();
    QString     dir;
    if(!curFile.isEmpty()){
        QFileInfo   fileInfo(curFile);
        dir     = fileInfo.canonicalPath();
    }
    
    return QFileDialog::getSaveFileName(this, tr("Save Doodle As..."), dir, tr("Doodle Files (*.d3x *.d3)"));
}

MainWindow*        DoodleMain::newMain() 
{ 
    return new DoodleMain(m_project);
}

void    DoodleMain::updateTitle()
{
    QString     t   = m_project->title();
    if(t.isEmpty())
        t   = tr("Untitled");
    if(m_project->isDirty())
        t += '*';
    
    if(m_number != 1){
        t += tr(" [%1]").arg(m_number);
    }
    
    QString     fn  = m_project->filename();
    if(!fn.isEmpty()){
        t += tr(" (%1)").arg(fn);
    }
    t += tr(" - DoodlerQt");
    setWindowTitle(t);
}

#include "moc_DoodleMain.cpp"

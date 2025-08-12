////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <art/logging.hpp>

#include "ArtMain.hpp"
#include "ArtApp.hpp"
#include "DocEditor.hpp"

#include <art/doc/Canvas.hpp>
#include <artQt/EditorQ.hpp>
#include <gluon/core/QtTypes.hpp>

#include <QMenuBar>
#include <QFileDialog>
//#include <doodleQt/Drawing2DWindow.hpp>
//#include <doodle/canvas/Drawing2D.hpp>
//#include <doodle/Project.hxx>

ArtMain::ArtMain() : ArtMain(defaultDocument())
{
}

ArtMain::ArtMain(DocumentQPtr doc) : UndoMainWindow(), 
    m_doc(doc), m_number(doc->takeANumber())
{
    ArtApp::increment();
    doc->incrementEditors();
    activateTabs();
    
    resize(1920, 1080);

    updateTitle();
    connect(doc.ptr(), &DocumentQ::titleChanged, this, &ArtMain::updateTitle);
    connect(doc.ptr(), &DocumentQ::fileChanged, this, &ArtMain::updateTitle);

    addAction("copy", "Copy").shortcut(QKeySequence::Copy);
    addAction("cut", "Cut").shortcut(QKeySequence::Cut);
    addAction("paste", "Paste").shortcut(QKeySequence::Paste);
    addAction("delete", "Delete").shortcut(QKeySequence::Delete);
    //addAction("new", "New Document").shortcut("Ctrl+Shift+N").connect(this, &ArtMain::cmdNew);
    addAction("open", "Open Document").shortcut(QKeySequence::New).connect(this, &ArtMain::cmdOpen);
    addAction("save", "Save Document").shortcut(QKeySequence::Save).connect(this, &ArtMain::cmdSave);
    addAction("saveas", "Save Document As").shortcut(QKeySequence::SaveAs).connect(this, &ArtMain::cmdSaveAs);
    //addAction("newdrawing", "New Drawing").shortcut("Ctrl+N").connect(this, &ArtMain::cmdNewDrawing);
    
    
    const EditorQMeta*      eqm = EditorQ::find(doc->metaInfo());
    if(eqm){
        m_editor    = eqm -> create(doc);
    }
    if(!m_editor)
        m_editor    = new DocEditor(doc);
    setCentralWidget(m_editor->qWidget());
    

    QMenu* fileMenu     = makeMenu("file", "File");
    QMenu* editMenu     = makeMenu("edit", "Edit");
    QMenu* viewMenu     = makeMenu("view", "View");
    
    for(auto& itr : m_editor->metaInfo().menus()){
        makeMenu(qString(itr.first), qString(itr.second));
    }
    
    QMenu* windowMenu   = makeMenu("window", "Window");
    QMenu* helpMenu     = makeMenu("help", "Help");

    menuBar()->addSeparator();
    QMenu* debugMenu    = makeMenu("debug", "Debug");

    addToMenu(fileMenu,
        QStringList() 
            << "new"
            << "open"
            << "--"
            << "newdrawing"
            << "--"
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
            << "--"
            << "newdrawing"
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
    
    m_editor -> configure(*this);
    
    //  and whatever else comes last (menus)
    
    doc->startAutoChecking();
}

ArtMain::~ArtMain()
{
    ArtApp::decrement();
    m_doc->decrementEditors();
}

#if 0
void    ArtMain::cmdNew()
{
    
}

void    ArtMain::cmdNewDrawing()
{
    if(!m_doc)
        return;
    
    using namespace yq::doodle;
    
    Drawing2D*   d          = m_doc->project().create<Drawing2D>();
    if(!d){
        yError() << "Unable to create a new drawing";
        return ;
    }
    
    Drawing2DWindow*dw      = new Drawing2DWindow(*m_doc, d->id());
    addWindow(dw);
}
#endif

void    ArtMain::cmdOpen()
{
}

void    ArtMain::cmdSave()
{
    if(m_doc->filename().isEmpty()){
        cmdSaveAs();
    } else {
        m_doc->save();
        updateTitle();
    }
}

void    ArtMain::cmdSaveAs()
{
    QString file    = getNewSaveFilename();
    if(file.isEmpty())
        return ;
    m_doc->saveAs(file);
    updateTitle();
}

void    ArtMain::cmdSaveCopy()
{
    QString file    = getNewSaveFilename();
    if(file.isEmpty())
        return ;
    m_doc->saveTo(file);
}

QString         ArtMain::getNewSaveFilename()
{
    QString     curFile = m_doc->filename();
    QString     dir;
    if(!curFile.isEmpty()){
        QFileInfo   fileInfo(curFile);
        dir     = fileInfo.canonicalPath();
    }
    
    return QFileDialog::getSaveFileName(this, tr("Save Art As..."), dir, tr("Art Files (*.art)"));
}

MainWindow*        ArtMain::newMain() 
{ 
    return new ArtMain(m_doc);
}

void    ArtMain::updateTitle()
{
    QString     t   = m_doc->title();
    if(t.isEmpty())
        t   = tr("Untitled");
    if(m_doc->isDirty())
        t += '*';
    
    if(m_number != 1){
        t += tr(" [%1]").arg(m_number);
    }
    
    QString     fn  = m_doc->filename();
    if(!fn.isEmpty()){
        t += tr(" (%1)").arg(fn);
    }
    t += tr(" - Art");
    setWindowTitle(t);
}

#include "moc_ArtMain.cpp"

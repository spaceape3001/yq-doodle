################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(Qt6 REQUIRED Core Gui Widgets )
set(CMAKE_AUTOMOC ON)

add_library(yq_artQt SHARED
    CanvasQ.hpp
    CanvasQ.cpp
    CanvasScene.hpp
    CanvasScene.cpp
    CanvasView.hpp
    CanvasView.cpp
    
    DocumentQ.hpp
    DocumentQ.cpp
    EditorQ.cpp
    
    SceneQ.hpp
    SceneQ.cpp
    
    ViewQ.hpp
    ViewQ.cpp

    artQt.cpp
)

target_link_libraries(yq_artQt
    PUBLIC
        yq_art
        yq_gluon
)
LinkTest(yq_artQt)

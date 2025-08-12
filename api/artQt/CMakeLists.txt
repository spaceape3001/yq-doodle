################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(Qt6 REQUIRED Core Gui Widgets )
set(CMAKE_AUTOMOC ON)

add_library(yq_artQt SHARED
    DocumentQ.hpp
    DocumentQ.cpp
    EditorQ.cpp
    
    canvas/CanvasQ.hpp
    canvas/CanvasQ.cpp
    canvas/CanvasScene.hpp
    canvas/CanvasScene.cpp
    canvas/CanvasView.hpp
    canvas/CanvasView.cpp

    kit/SceneQ.hpp
    kit/SceneQ.cpp
    kit/ViewQ.hpp
    kit/ViewQ.cpp
)

target_link_libraries(yq_artQt
    PUBLIC
        yq_art
        yq_gluon
)
LinkTest(yq_artQt)

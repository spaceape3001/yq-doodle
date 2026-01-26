################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_artQt)

find_package(Qt6 REQUIRED Core Gui Widgets )
set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED
    DocumentQ.hpp
    DocumentQ.cpp
    
    canvas/CanvasQ.hpp
    canvas/CanvasQ.cpp
    canvas/CanvasScene.hpp
    canvas/CanvasScene.cpp
    canvas/CanvasView.hpp
    canvas/CanvasView.cpp

    kit/EditorQ.cpp
    kit/GraphicsQ.hpp
    kit/GraphicsQ.cpp
    kit/SceneQ.hpp
    kit/SceneQ.cpp
    kit/ToolBarQ.hpp
    kit/ToolBarQ.cpp
    kit/ViewQ.hpp
    kit/ViewQ.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        yq_art
        yq_gluon
        yq_graphicsQt
)

yq_qtlib(${PROJECT_NAME})
LinkTest(${PROJECT_NAME})

################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(Qt6 COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)

add_library(yq_doodleQt SHARED
    Drawing2DWindow.hpp
    Drawing2DWindow.cpp
    DObjectTableModel.hpp
    DObjectTableModel.cpp
    ProjectQ.hpp
    ProjectQ.cpp

    #canvas/Canvas2DEdit.hpp
    #canvas/Canvas2DEdit.cpp
    canvas/Canvas2DScene.hpp
    canvas/Canvas2DScene.cpp
    canvas/Canvas2DView.hpp
    canvas/Canvas2DView.cpp
    canvas/Canvas2DWindow.hpp
    canvas/Canvas2DWindow.cpp
)

target_link_libraries(yq_doodleQt
    PUBLIC
        yq_gluon
        yq_doodle
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

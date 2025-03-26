################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(Qt6 COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)

add_library(yq_doodleQt SHARED
    DObjectTableModel.hpp
    DObjectTableModel.cpp
    ProjectQ.hpp
    ProjectQ.cpp
)

target_link_libraries(yq_doodleQt
    PUBLIC
        yq_gluon
        yq_doodle
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

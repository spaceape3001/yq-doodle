################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(Qt6 COMPONENTS Core Gui Widgets)

add_library(yq_doodleQt SHARED
    ProjectQ.hpp
    ProjectQ.cpp
)

target_link_libraries(yq_doodleQt
    PUBLIC
        yq_doodle
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

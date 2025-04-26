################################################################################
##
##  YOUR QUILL
##
################################################################################

project(doodlerQt)

find_package(Qt6 COMPONENTS Core Gui Widgets Svg SvgWidgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(doodlerQt 
    main.cpp
    DoodleApp.hpp
    DoodleApp.cpp
    DoodleMain.hpp
    DoodleMain.cpp
)

target_link_libraries(doodlerQt PUBLIC 
    yq_doodleQt
    yq_gluon 
    yq_process
)

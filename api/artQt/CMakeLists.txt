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

    artQt.cpp
)

target_link_libraries(yq_artQt
    PUBLIC
        yq_art
        yq_gluon
)
LinkTest(yq_artQt)

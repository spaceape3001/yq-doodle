################################################################################
##
##  YOUR QUILL
##
################################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(artQt 

    ArtApp.hpp
    ArtApp.cpp
    ArtMain.hpp
    ArtMain.cpp

    CanvasEditor.hpp
    CanvasEditor.cpp
    DocEditor.hpp
    DocEditor.cpp

    main.cpp
)

target_link_libraries(artQt PUBLIC
    yq_art
    yq_artQt
    yq_gluon
    yq_process
)

target_include_directories(artQt PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

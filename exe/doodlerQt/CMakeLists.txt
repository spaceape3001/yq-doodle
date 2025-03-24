################################################################################
##
##  YOUR QUILL
##
################################################################################

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

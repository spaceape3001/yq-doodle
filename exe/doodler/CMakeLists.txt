################################################################################
##
##  YOUR QUILL
##
################################################################################

add_executable(doodler 
    main.cpp
    DoodleApp.cpp
    DoodleMW.cpp
)

target_link_libraries(doodler 
PUBLIC 
    yq_doodle 
    yq_tachyon 
    yq_doodleVk
)

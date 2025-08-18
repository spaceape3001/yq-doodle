################################################################################
##
##  YOUR QUILL
##
################################################################################


add_executable(art 
    main.cpp
    ArtApp.cpp
    ArtMW.cpp
)

target_link_libraries(art 
PUBLIC 
    yq_art
    yq_tachyon 
    yq_artVk
)

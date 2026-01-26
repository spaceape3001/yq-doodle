################################################################################
##
##  YOUR QUILL
##
################################################################################

add_subdirectory(art)
add_subdirectory(b3)
add_subdirectory(doodle)

if(Build_Qt6)
    add_subdirectory(artQt)
    add_subdirectory(doodleQt)
endif()
if(Build_Vulkan)
    add_subdirectory(artvk)
    add_subdirectory(doodlevk)
endif()

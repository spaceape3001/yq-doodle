################################################################################
##
##  YOUR QUILL
##
################################################################################

add_subdirectory(3x)

if(Build_Qt6)
    add_subdirectory(doodlerQt)
    add_subdirectory(dizzyQt)
endif()
if(Build_Vulkan)
    add_subdirectory(doodler)
    add_subdirectory(dizzy)
endif()

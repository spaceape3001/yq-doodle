################################################################################
##
##  YOUR QUILL
##
################################################################################

add_subdirectory(b3)

if(Build_Qt6)
    # temporarily disabled
    #add_subdirectory(doodlerQt)
    add_subdirectory(artQt)
endif()
if(Build_Vulkan)
    add_subdirectory(doodler)
endif()

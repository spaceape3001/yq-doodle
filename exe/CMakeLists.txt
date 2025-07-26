################################################################################
##
##  YOUR QUILL
##
################################################################################

add_subdirectory(3x)

if(Build_Qt6)
    # temporarily disabled
    #add_subdirectory(doodlerQt)
endif()
if(Build_Vulkan)
    add_subdirectory(doodler)
endif()

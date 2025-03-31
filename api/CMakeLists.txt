################################################################################
##
##  YOUR QUILL
##
################################################################################

set(YQ_DOODLE_API_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(doodle)

if(Build_Qt6)
    add_subdirectory(doodleQt)
endif()
if(Build_Vulkan)
    add_subdirectory(doodleVk)
endif()

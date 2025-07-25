################################################################################
##
##  YOUR QUILL
##
################################################################################

set(YQ_DOODLE_API_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(doodle)
add_subdirectory(diagram)

if(Build_Qt6)
    add_subdirectory(doodleQt)
    add_subdirectory(diagramQt)
endif()
if(Build_Vulkan)
    add_subdirectory(doodleVk)
    add_subdirectory(diagramVk)
endif()

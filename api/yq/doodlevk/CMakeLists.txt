################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_doodlevk)

add_library(${PROJECT_NAME} SHARED
    command/DoodleCommand.cpp
)

vulqan_library(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC yq_doodle yq_tachyon)

yq_vklib(${PROJECT_NAME})
LinkTest(${PROJECT_NAME})

################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_doodleVk)

add_library(${PROJECT_NAME} SHARED
    command/DoodleCommand.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC yq_doodle yq_tachyon)

LinkTest(${PROJECT_NAME})

################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_diagramVk)

add_library(${PROJECT_NAME} SHARED
    command/DiagramCommand.cpp
)

vulqan_library(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC yq_diagram yq_tachyon)

LinkTest(${PROJECT_NAME})

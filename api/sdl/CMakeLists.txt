################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_sdl)

add_library(${PROJECT_NAME} SHARED
    #Canvas.cpp
    DObject.cpp
    Drawing.cpp
    Project.cpp
    Surface.cpp
)

target_link_libraries( ${PROJECT_NAME} 
    PUBLIC 
        yq_math
        yq_xml
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${YQ_DOODLE_API_DIR}
)

LinkTest(${PROJECT_NAME})


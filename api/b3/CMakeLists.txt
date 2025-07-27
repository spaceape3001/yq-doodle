################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_b3)

add_library(${PROJECT_NAME} SHARED
    args.cpp
    context.cpp
    obj.cpp
    types.cpp
    parse.cpp
)

target_link_libraries( ${PROJECT_NAME} 
    PUBLIC 
        yq_color 
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${YQ_DOODLE_API_DIR}
)

LinkTest(${PROJECT_NAME})


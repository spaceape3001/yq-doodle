################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_b3)

add_library(${PROJECT_NAME} SHARED
    #style.cpp
    
    Context.cpp
    Doc.cpp
    Frame.cpp
    Obj.cpp
    Parser.cpp
    
    annotate/Style.cpp
    
    spatial/Lineal.cpp
    spatial/Point.cpp
    
    terrain/Terrain.cpp
    terrain/TileGroup.cpp
    
    util/ArgList.cpp
    util/ArgMap.cpp
    util/parse.cpp
    util/types.cpp
)

target_link_libraries( ${PROJECT_NAME} 
    PUBLIC 
        yq_core 
        yq_math 
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${YQ_DOODLE_API_DIR}
)

LinkTest(${PROJECT_NAME})


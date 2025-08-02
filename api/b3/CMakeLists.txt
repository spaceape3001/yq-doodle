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
    MapPainter.cpp
    Obj.cpp
    Parser.cpp
    
    cmds/basic.cpp
    cmds/building.cpp
    cmds/frame.cpp
    cmds/point.cpp
    cmds/style.cpp
    cmds/terrain.cpp
    
    annotate/Style.cpp
    
    #format/SvgPainter.cpp
    
    handler/docmap.cpp
    
    paint/SvgGenerator.cpp
    
    spatial/Areal.cpp
    spatial/Linear.cpp
    spatial/Point.cpp
    spatial/PointLine.cpp
    spatial/PointType.cpp
    spatial/Vertical.cpp
    
    terrain/StdTerrain.cpp
    terrain/TerPage.cpp
    terrain/Terrain.cpp
    terrain/TerTile.cpp
    terrain/TileGroup.cpp
    
    util/ArgList.cpp
    util/ArgMap.cpp
    util/parse.cpp
    util/types.cpp
)

target_link_libraries( ${PROJECT_NAME} 
    PUBLIC 
        yq_core 
        yq_file
        yq_math
        
    PRIVATE
        yq_xml 
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${YQ_DOODLE_API_DIR}
)

LinkTest(${PROJECT_NAME})


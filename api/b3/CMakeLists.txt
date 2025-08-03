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
    Painter.cpp
    Parser.cpp

    annotate/Circle.cpp
    annotate/Label.cpp
    annotate/Polyline.cpp
    annotate/Style.cpp
    
    cmds/annotatecmds.cpp
    cmds/basiccmds.cpp
    cmds/buildingcmds.cpp
    cmds/framecmds.cpp
    cmds/gridcmds.cpp
    cmds/pointcmds.cpp
    cmds/stylecmds.cpp
    cmds/terraincmds.cpp
    
    #format/SvgPainter.cpp
    
    grid/grid.cpp
    
    map/map.cpp
    map/MapPainter.cpp

    paint/RasterGenerator.cpp
    paint/SvgGenerator.cpp
    
    spatial/spatial.cpp
    
    terrain/StdTerrain.cpp
    terrain/TerPage.cpp
    terrain/Terrain.cpp
    terrain/TerTile.cpp
    terrain/TileGroup.cpp
    
    util/util.cpp
)

target_link_libraries( ${PROJECT_NAME} 
    PUBLIC 
        yq_core 
        yq_file
        yq_math
        yq_xml 
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${YQ_DOODLE_API_DIR}
)

LinkTest(${PROJECT_NAME})


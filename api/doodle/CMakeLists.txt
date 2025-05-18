################################################################################
##
##  YOUR QUILL
##
################################################################################

#   Spatial is meant to be a fast doodle relation capability, so rather than 
#   focusing on lines/rectangles, we focus on objects, like chairs, rooms, windows, etc.

#   SUPERSCRIPTS ⁰ ¹ ² ³ ⁴ ⁵ ⁶ ⁷ ⁸ ⁹ ʰ ᵖ ⁿ ʳ ˢ ᵗ ᵘ ᵛ ʷ ˣ ʸ ᶻ
#   Numbers ① ② ③ ④

add_library(yq_doodle SHARED

    Association.cpp
    Camera.cpp
    Canvas.cpp
    Constraint.cpp
    DObject.cpp
    Evaluator.cpp
    Light.cpp
    Motion.cpp
    Project.cpp
    Py.cpp

    Space.cpp
 
    bit/ID.cpp
    bit/SStringMap.cpp
    
    canvas/Canvas2D.cpp
    canvas/Drawing2D.cpp
    
    io/b3grammar.cpp

    py/Curve.cpp
    py/Point.cpp
    
    space/Space1D.cpp
    space/Space2D.cpp
#    Space2Z.cpp
    space/Space3D.cpp
    space/Space4D.cpp
    
        #   Two letters are being assigned for dimension/coordinate systems
    #   0D is zero dimensional (almost useless TBH)

    #   1D is pure one dimensional
   
    #   1Y is mainly 1D dimension with a second (minor) coordinate
    #   So 1D & 1D is supported
    
    #   1Z is mainly 1D dimension with a second/third (minor) coordinates 
    #   (note Y will be considered to be of greater importance than Z)
    
    #   2C is three dimensional cylindrical coordinates, its z is considered minor (like 2Z)
    
    #   2D is pure two dimensions
    #   2G is three dimensional geodetic coordinates where Z (altitude) is considered minor
    
    #   2P is pure two dimensions with polar coordinates
    
    #   2S is spherical coordinates (z is either minor or not present)
    
    #   2Z is three dimensions with the z considered "minor" ... so think a plat map
    
    #   3C is three dimensional cylindrical coordinates
    
    
    #   3G  is three dimensional geodetic coordinates
    
    
    #   3S  is spherical coordinates
)

target_link_libraries(yq_doodle
    PUBLIC
        yq_color
        yq_core
        yq_math
        yq_userexpr
        yq_xml
)

target_include_directories(yq_doodle
    PUBLIC
        ${YQ_DOODLE_API_DIR}
)

target_compile_definitions(yq_doodle
    PRIVATE 
        "-DYQ_DOODLE_DATA_DIR=\"${YQ_DOODLE_DATA_DIR}\"" 
)

LinkTest(yq_doodle)


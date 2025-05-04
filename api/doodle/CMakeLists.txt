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
    Constraint.cpp
    DObject.cpp
    Light.cpp
    Motion.cpp
    Project.cpp
    Py.cpp
    Space.cpp
    
    #   Two letters are being assigned for dimension/coordinate systems
    
    #   0D is zero dimensional (almost useless TBH)
    0D/Py0D.cpp

    #   1D is pure one dimensional
    1D/Py1D.cpp
    
    #   1Y is mainly 1D dimension with a second (minor) coordinate
    #   So 1D & 1D is supported
    
    #   1Z is mainly 1D dimension with a second/third (minor) coordinates 
    #   (note Y will be considered to be of greater importance than Z)
    
    #   2C is three dimensional cylindrical coordinates, its z is considered minor (like 2Z)
    
    #   2D is pure two dimensions
    2D/Drawing2D.cpp
    2D/Page2D.cpp
    2D/Py2D.cpp
    2D/Space2D.cpp
    
    #   2G is three dimensional geodetic coordinates where Z (altitude) is considered minor
    
    #   2P is pure two dimensions with polar coordinates
    
    #   2S is spherical coordinates (z is either minor or not present)
    
    #   2Z is three dimensions with the z considered "minor" ... so think a plat map
    2Z/Space2Z.cpp
    
    #   3C is three dimensional cylindrical coordinates
    
    3D/Py3D.cpp
    3D/Space3D.cpp
    
    #   3G  is three dimensional geodetic coordinates
    
    
    #   3S  is spherical coordinates
    
    
    4D/Py4D.cpp
    4D/Space4D.cpp
    
    bit/SStringMap.cpp
    bit/ID.cpp
    
    io/b3grammar.cpp
    
)

target_link_libraries(yq_doodle
    PUBLIC
        yq_color
        yq_core
        yq_math
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


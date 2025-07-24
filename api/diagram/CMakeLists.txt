################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_diagram)

#   Diagraming... no abstractions, simple/lighter weight

#   SUPERSCRIPTS ⁰ ¹ ² ³ ⁴ ⁵ ⁶ ⁷ ⁸ ⁹ ʰ ᵖ ⁿ ʳ ˢ ᵗ ᵘ ᵛ ʷ ˣ ʸ ᶻ
#   Numbers ① ② ③ ④
#   Greek Δ δ


add_library(${PROJECT_NAME} SHARED
    DObject.cpp
    Project.cpp

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

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        yq_color
        yq_core
        yq_math
        yq_userexpr
        yq_xml
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${YQ_DOODLE_API_DIR}
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE 
        "-DYQ_DIAGRAM_DATA_DIR=\"${YQ_DOODLE_DATA_DIR}\"" 
)

LinkTest(${PROJECT_NAME})


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

    Py.cpp
    DDocument.cpp
    DObject.cpp
    
    0D/Py0.cpp
    1D/Py1.cpp
    3D/Py3.cpp
    4D/Py4.cpp
    
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

LinkTest(yq_doodle)


################################################################################
##
##  YOUR QUILL
##
################################################################################

#   3X is meant to be a fast command line processor for graphics processing
#   (STL generation, SVG generation, etc)  Might split into separate executables

add_executable(b3 
    b3.cpp
    debug.cpp
    maps.cpp
    points.cpp
)
target_link_libraries(b3 
    PUBLIC 
        yq_b3
        yq_file
        yq_process
)

################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_doodleVk SHARED
    command/DoodleCommand.cpp
)

target_link_libraries(yq_doodleVk PUBLIC yq_doodle yq_tachyon)

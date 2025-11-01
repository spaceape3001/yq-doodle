################################################################################
##
##  YOUR QUILL
##
################################################################################


add_library(yq_artVk SHARED
    ArtDocPtr.cpp
    DocTypeMenuUI.cpp
)

target_link_libraries(yq_artVk
    PUBLIC
        yq_art
        yq_tachyon
)
LinkTest(yq_artVk)

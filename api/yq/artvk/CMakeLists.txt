################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_artvk)

add_library(${PROJECT_NAME} SHARED
    ArtDocPtr.cpp
    DocTypeMenuUI.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        yq_art
        yq_tachyon
        yq_assetvk
)

yq_vklib(${PROJECT_NAME})
LinkTest(${PROJECT_NAME})

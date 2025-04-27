################################################################################
##
##  YOUR QUILL
##
################################################################################

find_package(Qt6 COMPONENTS Core Gui Widgets)
set(CMAKE_AUTORCC ON)

add_library(yq_doodleResources SHARED yqDoodleResources.cpp yqDoodleResources.qrc)
target_link_libraries(yq_doodleResources PUBLIC Qt6::Core)
target_include_directories(yq_doodleResources PUBLIC . )


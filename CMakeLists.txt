################################################################################
##
##  YOUR QUILL
##
################################################################################

cmake_minimum_required(VERSION 3.26.0)
project(doodle LANGUAGES CXX)

include(configure.cmake)

if(PROJECT_IS_TOP_LEVEL)
    if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/yq-toolbox)
        message(FATAL_ERROR "YQ toolbox must be present! (use a symbolic link or junction)")
    endif()

    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/qt-utilities)
        option(Feature_Qt6      "Enable Qt6 (API and Apps)" ON)
        set(Build_Qt6 ${Feature_Qt6})
    else()
        set(Build_Qt6 OFF)
    endif()

    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/yq-vulqan)
        option(Feature_Vulkan   "Enable Vulkan (API and Apps)" OFF)
        set(Build_Vulkan ${Feature_Vulkan})
    else()
        set(Build_Vulkan OFF)
    endif()
    
    
    include(yq-toolbox/configure.cmake)
    add_subdirectory(yq-toolbox)
    
    if(Build_Vulkan)
        include(yq-vulqan/configure.cmake)
        add_subdirectory(yq-vulqan)
    endif()
    
    if(Build_Qt6)
        include(qt-utilities/configure.cmake)
        add_subdirectory(qt-utilities)
        find_package(Qt6 COMPONENTS Core)
    endif()
    
else()
    #   We're a sub-project, configure
    if(NOT YOUR_QUILL_TOOLBOX)
        message(FATAL_ERROR "YQ toolbox must be used!")
    endif()

endif()

enable_testing()

add_subdirectory(api)
add_subdirectory(test)
add_subdirectory(exe)

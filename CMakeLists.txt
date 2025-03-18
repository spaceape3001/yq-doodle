################################################################################
##
##  YOUR QUILL
##
################################################################################

cmake_minimum_required(VERSION 3.26.0)
project(doodle LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
    option(Feature_Qt6      "Enable Qt6 (API and Apps)" ON)
    option(Feature_Vulkan   "Enable Vulkan (API and Apps)" ON)
    set(Build_Qt6           ${Feature_Qt6})
    set(Build_Vulkan        ${Feature_Vulkan})
endif()


if(NOT YOUR_QUILL_TOOLBOX)
    if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/yq-toolbox)
        message(FATAL_ERROR "YQ toolbox must be present! (use a symbolic link or junction)")
    endif()
    
    include(yq-toolbox/configure.cmake)
    add_subdirectory(yq-toolbox)
endif()

if(Build_Vulkan)
    if(NOT YOUR_QUILL_VULQAN)
    endif()
endif()

enable_testing()

add_subdirectory(api)
add_subdirectory(test)

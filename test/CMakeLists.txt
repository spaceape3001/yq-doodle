################################################################################
##
##  YOUR QUILL
##
################################################################################

macro(doodle_test name)
    add_executable(test_${name} ${name}.cpp)
    target_link_libraries(test_${name} PRIVATE yq_doodle BoostUT)
    add_test(NAME ${name} COMMAND test_${name} ${ARGN})
endmacro()

#doodle_test(b3parse)
#doodle_test(evaluator)

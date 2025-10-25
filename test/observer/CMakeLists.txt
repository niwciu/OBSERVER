#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building Unit test modules.
#
# usage:
#        For build using Unix Makefiles:
#          	1. cmake -S./ -B out -G"Unix Makefiles"
#			2. enter the "out" folder
#          	3. make all -o observer_test.o (-jXX additionaly to speed up)
#        For build using Ninja:
#          	1. cmake -S./ -B out -G"Ninja"
# 			2. enter the "out" folder
#         	3. ninja -C out -o observer_test.o (optional with -V  and -jxx ->xx numnber of cores)
# additional custom targets for this project:
# 		If lizard is installed and you are in the out folder:
# 			1. make ccm -> code complexity metrix print in console
# 			2. make ccmr -> code complexity metrics report generation
# 		If cppcheck is installed and you are in the out folder
# 			1. make cppcheck_src -> static analize  for src folder printed in console
# 			2. make cppcheck_test-> static analize  for src folder printed in console
# 		If gcovr is installed and you are in the out folder
# 			1. make ccr -> code coverage report generation 
# 
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)
project(observer_test C)

# --- Add subdirectories for libraries ---
add_subdirectory(../unity unity_build)          # unity static library
add_subdirectory(../../lib/observer observer_build)  # observer_lib static library

# --- Include custom targets ---
set(CUSTOM_TARGETS_FILE_DIR ./custom_targets.cmake)
include(${CUSTOM_TARGETS_FILE_DIR})

# --- Test source files ---
set(TEST_SRCS
    observer_test_main.c
    observer_test_runner.c
    observer_subscribe_test.c
	observer_unsubscribe_test.c
	observer_notify_test.c
	observer_notify_with_state_arg_test.c
	observer_notify_with_u8_arg_test.c
	observer_subscribe_with_state_arg_test.c
	observer_subscribe_with_u8_arg_test.c
	observer_unsubscribe_with_state_arg_test.c
	observer_unsubscribe_with_u8_arg_test.c
	mock_fun.c
)

# --- Global defines (dla kompilatora) ---
set(GLOBAL_DEFINES
    -DUNIT_TESTS
)

# --- Create test executable ---
add_executable(${PROJECT_NAME} ${TEST_SRCS})

# --- Link precompiled libraries ---
target_link_libraries(${PROJECT_NAME} PRIVATE observer_lib unity)

# --- Include directories ---
target_include_directories(${PROJECT_NAME} PRIVATE ..)

# --- Apply global defines ---
target_compile_definitions(${PROJECT_NAME} PRIVATE ${GLOBAL_DEFINES})

# --- Compiler flags ---
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g3 -fshort-enums")
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
endif()

# --- Link math library if available ---
find_library(HAVE_LIB_M m)
if(HAVE_LIB_M)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()

# --- Conditional coverage flags ---
    target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_options(${PROJECT_NAME} PRIVATE -fprofile-arcs)
    target_compile_options(observer_lib PRIVATE -fprofile-arcs -ftest-coverage)
    target_link_options(observer_lib PRIVATE -fprofile-arcs)
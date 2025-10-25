#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building Unit test modules.
#
# usage:
#        For build using Unix Makefiles:
#          	1. cmake -S./ -B out -G"Unix Makefiles"
#			2. enter the "out" folder
#          	3. make all -o template_test.o (-jXX additionaly to speed up)
#        For build using Ninja:
#          	1. cmake -S./ -B out -G"Ninja"
# 			2. enter the "out" folder
#         	3. ninja -C out -o template_test.o (optional with -V )
# 
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)
project(basic_integer_example C)

# --- Add subdirectories for libraries ---
add_subdirectory(../../lib/observer observer_build)  # creates 'observer_lib' static library

# --- Include custom targets ---
set(CUSTOM_TARGETS_FILE_DIR ./custom_targets.cmake)
include(${CUSTOM_TARGETS_FILE_DIR})

# --- Test source files ---
set(SRCS
    main.c
    mock_display.c
    mock_state_machine.c
)

# --- Create test executable ---
add_executable(${PROJECT_NAME} ${SRCS})

# --- Link precompiled libraries (observer + Unity) ---
target_link_libraries(${PROJECT_NAME} PRIVATE observer_lib)

# --- Optional: include directories for test sources ---
# biblioteki propagują include path automatycznie, więc tu wystarczy katalog z testami
# target_include_directories(${PROJECT_NAME} PRIVATE ..)

# --- Compiler definitions for test target ---
# target_compile_definitions(${PROJECT_NAME} PRIVATE UNIT_TESTS)

# --- Compiler flags ---
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g3 -fshort-enums")
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
endif()

# --- Optional: link math library if available ---
find_library(HAVE_LIB_M m)
if(HAVE_LIB_M)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()


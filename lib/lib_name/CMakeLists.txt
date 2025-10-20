cmake_minimum_required(VERSION 3.20)

add_library(queue_lib STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/queue.c    
)

set_target_properties(queue_lib PROPERTIES 
  OUTPUT_NAME "queue_lib"
  PREFIX ""
)

target_include_directories(queue_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
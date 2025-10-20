cmake_minimum_required(VERSION 3.20)

add_library(observer_lib STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/observer.c    
)

set_target_properties(observer_lib PROPERTIES 
  OUTPUT_NAME "observer_lib"
  PREFIX ""
  )

target_include_directories(observer_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

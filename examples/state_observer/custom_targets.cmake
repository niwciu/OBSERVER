# PROJECT CUSTOM TARGETS FILE
#  here you can define custom targets for the project so all team member can use it in the same way
#  some example of custo targets are shown bello those are targets for:
# 		1. Running example


#TARGETS FOR RUNNING UNIT TESTS
message(STATUS "To run example, you can use predefine target: \r\n\trun,")
add_custom_target(run basic_integer_example)

#TARGETS FOR RUNNING CLANG-FORMAT on example code
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
	message(STATUS "clang-format was found, you can use predefined target for formating the code in project predefined standard : \r\n\tformat")
else()
	message(STATUS "clang-format was not found. \r\n\tInstall clang-format to get predefined target for formating the code in project predefined standard")
endif()
add_custom_target(format  clang-format -i -style=file 
						../*.c 
						../*.h)


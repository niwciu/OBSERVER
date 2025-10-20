# PROJECT CUSTOM TARGETS FILE
#  here you can define custom targets for the project so all team member can use it in the same way
#  some example of custo targets are shown bello those are targets for:
# 		1. Running unit tests
# 		2. Code Complexity Metrics
# 		3. CppCheck static analize of specific folder
# 		4. Code Coverage report generation.


#TARGETS FOR RUNNING UNIT TESTS
message(STATUS "You can use predefined target to run unit tests: \r\n\trun,")
add_custom_target(run observer_test)

# TARGET FOR CHECKING CODE COMPLEXITY METRICS"
# check if lizard software is available 
find_program(lizard_program lizard)
if(lizard_program)
	message(STATUS "Lizard was found, you can use predefined targets for src folder Code Complexity Metrics: \r\n\tccm,\r\n\tccmr,")
else()
	message(STATUS "Lizard was not found. \r\n\tInstall Lizard to get predefined targets for src folder Code Complexity Metrics")
endif()
# Prints CCM for src folder in the console
add_custom_target(ccm lizard 
						../../../lib/observer 
						--CCN 12 
						-Tnloc=30 
						-a 4 
						--languages cpp 
						-V 
						-i 0)
# Create CCM report in reports/Cylcomatic_Complexity/
add_custom_command(
    OUTPUT ../../../reports/CCM/
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCM/
    COMMENT "Tworzenie katalogów raportów Code Coverage"
)
# Create CCM report in reports/Cylcomatic_Complexity/
add_custom_target(ccmr 
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCM/
	COMMAND lizard 
				../../../lib/observer
				--CCN 12 
				-Tnloc=30 
				-a 4 
				--languages cpp 
				-V 
				-o ../../../reports/CCM/observer.html)

# TARGET FOR MAKING STATIC ANALYSIS OF THE SOURCE CODE AND UNIT TEST CODE
# check if cppchec software is available 
find_program(cppcheck_program cppcheck)
if(cppcheck_program)
	message(STATUS "CppCheck was found, you can use predefined targets for static analize : \r\n\tcppcheck,")
else()
	message(STATUS "CppCheck was not found. \r\n\tInstall CppCheck to get predefined targets for static analize")
endif()
# Prints static analize output for src folder in the console
add_custom_target(cppcheck cppcheck
					../../../lib/observer
					../../../test/observer
					-i../../../test/observer/out
					--enable=all
					--force
					# --inconclusive
					--std=c99
					# --inline-suppr 
					# --platform=win64 
					--suppress=missingIncludeSystem 
					--suppress=missingInclude
					# --suppress=constParameterPointer:../../../test/observer/mock_switch.c:21
					# --suppress=constParameterPointer:../../../test/observer/mock_switch.c:32
					--checkers-report=cppcheck_checkers_report.txt
					--check-level=exhaustive
					--error-exitcode=1
					)

# TARGET FOR CREATING CODE COVERAGE REPORTS
# check if python 3 and gcovr are available 
find_program(GCOVR gcovr)
if(GCOVR)
	message(STATUS "python 3 and gcovr was found, you can use predefined targets for uint tests code coverage report generation : 
					\r\tccc - Code Coverage Check, 
					\r\tccr - Code Coverage Reports generation,
					\r\tccca - Code Coverage Check All -> whole project check, 
					\r\tccra - Code Coverage Reports All -> whole project raport generation")
else()
	message(STATUS "pyton 3 was found but gcovr was not found. \r\n\tInstall gcovr to get predefined targets for uint tests code coverage report generation")
endif()
add_custom_command(
    OUTPUT ../../../reports/CCR/ ../../../reports/CCR/JSON_ALL/
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/
    COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/JSON_ALL/
    COMMENT "Tworzenie katalogów raportów Code Coverage"
)
add_custom_target(ccr
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/observer
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/JSON_ALL/
	COMMAND gcovr 
				-r ../../../lib/observer  
				--json ../../../reports/CCR/JSON_ALL/coverage_observer.json
				--json-base  lib/observer
				--html-details ../../../reports/CCR/observer/observer_report.html 
				.)
add_custom_target(ccc gcovr  
						-r ../../../lib/observer 
						.)

add_custom_target(ccca gcovr  
						-r ../../../ 
						--json-add-tracefile \"../../../reports/CCR/JSON_ALL/coverage_*.json\"  
						.)
						
add_custom_target(ccra  
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/
	COMMAND ${CMAKE_COMMAND} -E make_directory ../../../reports/CCR/JSON_ALL/
	COMMAND gcovr 
				-r ../../../ 
				--json-add-tracefile \"../../../reports/CCR/JSON_ALL/coverage_*.json\"  
				--html-details -o ../../../reports/CCR/JSON_ALL/HTML_OUT/project_coverage.html
				--html-theme github.dark-green
				.
)
add_dependencies(ccra ccr)
add_dependencies(ccca ccr)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
	message(STATUS "clang-format was found, you can use predefined target for formating the code in project predefined standard : \r\n\tformat \r\n\tformat_test")
else()
	message(STATUS "clang-format was not found. \r\n\tInstall clang-format to get predefined target for formating the code in project predefined standard")
endif()
add_custom_target(format  clang-format -i -style=file 
						../../../lib/observer/*.c 
						../../../lib/observer/*.h)

add_custom_target(format_test  clang-format -i -style=file 
						../*.c
						../*.h)
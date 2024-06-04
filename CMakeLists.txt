cmake_minimum_required(VERSION 3.10)

project(linearalgebra VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set runtime library
if (MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
endif()


file(GLOB_RECURSE LIB_HEADERS "include/**/*.h")
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")


# Define the library
add_library(LinearAlgebra STATIC ${LIB_SOURCES})

# Include directories
target_include_directories(LinearAlgebra PUBLIC include)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# Now simply link against gtest or gtest_main as needed. Eg
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")


# Define a function to add tests
function(add_library_test TEST_FILE)
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_FILE})
  target_link_libraries(${TEST_NAME} gtest_main LinearAlgebra)
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

# Loop over each test file and add it
foreach(TEST_FILE ${TEST_SOURCES})
  add_library_test(${TEST_FILE})
endforeach()

# Enable testing
enable_testing()


cmake_minimum_required(VERSION 3.0)
project(TestFindTBB VERSION 1.0.0 LANGUAGES CXX)

# Set the RPATH of executable
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Find external project via CMake config file
# The external project depends on TBB

find_package(TestFindTBB CONFIG REQUIRED HINTS ${TESTFINDTBB_ROOT_DIR})

# ==============================================================================
# Test building executables and libraries that use TBB

# Test transitive linking of FindTBB target
add_executable(test_tbb test_tbb.cc)
target_link_libraries(test_tbb sum)


install(TARGETS test_tbb
    RUNTIME DESTINATION bin)

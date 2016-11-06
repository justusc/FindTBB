cmake_minimum_required(VERSION 3.0)
project(TestFindTBB VERSION 1.0.0 LANGUAGES CXX)

# Add FindTBB.cmake path file to the module path
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/..")

# Set RPATHS in executables
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")


# ==============================================================================
# Print input variables used by FindTBB.cmake

message("CMAKE_SYSTEM_NAME = '${CMAKE_SYSTEM_NAME}'")
message("CMAKE_BUILD_TYPE  = '${CMAKE_BUILD_TYPE}'")

message("User Input Variables:")
message("TBB_ROOT_DIR = '${TBB_ROOT_DIR}'")
message("TBB_INCLUDE_DIR = '${TBB_INCLUDE_DIR}'")
message("TBB_LIBRARY = '${TBB_LIBRARY}'")
message("TBB_tbb_LIBRARY = '${TBB_tbb_LIBRARY}'")
message("TBB_tbb_debug_LIBRARY = '${TBB_tbb_debug_LIBRARY}'")
message("TBB_tbbmalloc_LIBRARY = '${TBB_tbbmalloc_LIBRARY}'")
message("TBB_tbbmalloc_debug_LIBRARY = '${TBB_tbbmalloc_debug_LIBRARY}'")
message("TBB_tbb_preview_LIBRARY = '${TBB_tbb_preview_LIBRARY}'")
message("TBB_tbb_preview_debug_LIBRARY = '${TBB_tbb_preview_debug_LIBRARY}'")
message("TBB_USE_DEBUG_BUILD = '${TBB_USE_DEBUG_BUILD}'")

message("Environment Varaibles used by FindTBB:")
message("TBB_INSTALL_DIR = '$ENV{TBB_INSTALL_DIR}'")
message("TBBROOT         = '$ENV{TBBROOT}'")
message("LIBRARY_PATH    = '$ENV{LIBRARY_PATH}'")

#find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy tbb_preview)
find_package(TBB)


# ==============================================================================
# Print output variables from FindTBB.cmake

set(TBB_SEARCH_COMPOMPONENTS tbb_preview tbbmalloc_proxy tbbmalloc tbb)

message("FindTBB Result Variables:")
message("TBB_FOUND = '${TBB_FOUND}'")
message("TBB_tbbmalloc_FOUND = '${TBB_tbbmalloc_FOUND}'")
message("TBB_tbbmalloc_proxy_FOUND = '${TBB_tbbmalloc_FOUND}'")
message("TBB_tbb_preview_FOUND = '${TBB_tbb_preview_FOUND}'")
message("TBB_VERSION = '${TBB_VERSION}'")
message("TBB_VERSION_MAJOR = '${TBB_VERSION_MAJOR}'")
message("TBB_VERSION_MINOR = '${TBB_VERSION_MINOR}'")
message("TBB_INTERFACE_VERSION = '${TBB_INTERFACE_VERSION}'")
foreach(_comp ${TBB_SEARCH_COMPOMPONENTS})
  message("TBB_${_comp}_LIBRARY_RELEASE = '${TBB_${_comp}_LIBRARY_RELEASE}'")
  message("TBB_${_comp}_LIBRARY_DEBUG = '${TBB_${_comp}_LIBRARY_DEBUG}'")
  message("TBB_${_comp}_LIBRARY = '${TBB_${_comp}_LIBRARY}'")
endforeach()

message("FindTBB Output Variables:")
message("TBB_INCLUDE_DIRS = '${TBB_INCLUDE_DIRS}'")
message("TBB_LIBRARIES_RELEASE = '${TBB_LIBRARIES_RELEASE}'")
message("TBB_LIBRARIES_DEBUG = '${TBB_LIBRARIES_DEBUG}'")
message("TBB_LIBRARIES = '${TBB_LIBRARIES}'")
message("TBB_DEFINITIONS = '${TBB_DEFINITIONS}'")


message("TBB_INCLUDE_DIRS = '${TBB_INCLUDE_DIRS}'")
message("TBB_LIBRARIES_RELEASE = '${TBB_LIBRARIES_RELEASE}'")
message("TBB_LIBRARIES_DEBUG = '${TBB_LIBRARIES_DEBUG}'")
message("TBB_LIBRARIES = '${TBB_LIBRARIES}'")
message("TBB_DEFINITIONS = '${TBB_DEFINITIONS}'")


# ==============================================================================
# Test building executables and libraries that use TBB

# Test linking TBB via FindTBB output variables
add_executable(test_tbb_a test_tbb.cc sum.h sum.cc)
target_include_directories(test_tbb_a PRIVATE ${TBB_INCLUDE_DIRS})
target_compile_definitions(test_tbb_a PRIVATE ${TBB_DEFINITIONS})
target_compile_options(test_tbb_a PRIVATE "-std=c++11")
target_link_libraries(test_tbb_a ${TBB_LIBRARIES})

# Test linking TBB to a library via the FindTBB target
add_library(sum SHARED sum.cc sum.h)
set_target_properties(sum PROPERTIES PUBLIC_HEADER sum.h)
target_compile_options(sum PUBLIC "-std=c++11")
target_include_directories(sum PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/testfindtbb>)
target_link_libraries(sum tbb)

# Test transitive linking of FindTBB target
add_executable(test_tbb_b test_tbb.cc)
target_link_libraries(test_tbb_b sum)

# Install the test executables
install(TARGETS test_tbb_a test_tbb_b sum
    EXPORT testfindtbb COMPONENT testfindtbb
    RUNTIME        DESTINATION  bin
    PUBLIC_HEADER  DESTINATION  include/testfindtbb
    LIBRARY        DESTINATION  lib
    ARCHIVE        DESTINATION  lib)


# ==============================================================================
# Test exporting targets that depend on TBB

include(CMakePackageConfigHelpers)

# Create the project version file
write_basic_package_version_file(testfindtbb-config-version.cmake
    VERSION ${TESTFINDTBB_VERSION}
    COMPATIBILITY AnyNewerVersion)

# Create the project targets file
export(EXPORT testfindtbb
    FILE "${PROJECT_BINARY_DIR}/testfindtbb-targets.cmake")

# Create the project configure file
configure_package_config_file(cmake/testfindtbb-config.cmake.in
    "${PROJECT_BINARY_DIR}/testfindtbb-config.cmake"
     INSTALL_DESTINATION lib/cmake/testfindtbb
     PATH_VARS CMAKE_INSTALL_PREFIX)

# Install config, version, and target files for the project
install(EXPORT testfindtbb
    FILE "testfindtbb-targets.cmake"
    DESTINATION lib/cmake/testfindtbb
    COMPONENT testfindtbb)
install(FILES
    "${PROJECT_BINARY_DIR}/testfindtbb-config.cmake"
    "${PROJECT_BINARY_DIR}/testfindtbb-config-version.cmake"
    "${PROJECT_SOURCE_DIR}/../FindTBB.cmake"
    DESTINATION "lib/cmake/testfindtbb"
    COMPONENT testfindtbb)



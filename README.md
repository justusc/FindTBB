# FindTBB Module
FindTBB is a [CMake](http://www.cmake.org) find package module for [Intel&reg; Thread Building Blocks](https://www.threadingbuildingblocks.org) (TBB).

# Usage
The signature of the TBB find module in CMake is:
```CMake
find_package(TBB [major[.minor]] [EXACT] [QUIET] [REQUIRED]
             [COMPONENTS [tbbmalloc] [tbb_preview]]
             [OPTIONAL_COMPONENTS [tbbmalloc] [tbb_preview]]) 
```
where the allowed components are tbbmalloc and tbb_preview.

# User Variables
The following varibiles may be used by the user to specify the install, include, and/or library directories of TBB. 

* ```TBB_ROOT_DIR``` - The base directory the of TBB installation.
* ```TBB_INCLUDE_DIR```  - The directory that contains the TBB headers files.
* ```TBB_LIBRARY``` - The directory that contains the TBB library files.
* ```TBB_<library>_LIBRARY``` - The path of the corresponding TBB library. These libraries, if specified, override the corresponding library search results, where <library> may be tbb, tbb_debug, tbbmalloc, tbbmalloc_debug, tbb_preview, or tbb_preview_debug.
* ```TBB_USE_DEBUG_BUILD``` - The debug version of tbb libraries, if present, will be used instead of the release version.

In addition, FindTBB uses the following environment variables to find the TBB install directory.

* ```TBB_INSTALL_DIR```
* ```TBBROOT```
* ```LIBRARY_PATH```

# FindTBB Results
This module will set the following variables:

* ```TBB_FOUND``` - Set to false, or undefined, if we haven’t found, or don’t want to use TBB.
* ```TBB_<component>_FOUND``` - If False, optional <component> part of TBB sytem is not available.
* ```TBB_VERSION``` - The full version string
* ```TBB_VERSION_MAJOR``` - The major version
* ```TBB_VERSION_MINOR``` - The minor version
* ```TBB_INTERFACE_VERSION``` - The interface version number defined in tbb/tbb_stddef.h.
* ```TBB_<library>_LIBRARY_RELEASE``` - The path of the TBB release version of <library>, where <library> may be tbb, tbb_debug, tbbmalloc, tbbmalloc_debug, tbb_preview, or tbb_preview_debug.
* ```TBB_<library>_LIBRARY_DEGUG``` - The path of the TBB release version of <library>, where <library> may be tbb, tbb_debug, tbbmalloc, tbbmalloc_debug, tbb_preview, or tbb_preview_debug.

# Output Variables
The following varibles should be used to link executables and libraries with TBB:

* ```TBB_INCLUDE_DIRS``` - The include directory for TBB.
* ```TBB_LIBRARIES``` - The libraries to link against to use TBB.
* ```TBB_DEFINITIONS``` - Definitions to use when compiling code that uses TBB.

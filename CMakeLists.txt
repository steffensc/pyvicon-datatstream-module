cmake_minimum_required(VERSION 3.5)

################################
function(PRINT_VAR VARNAME)
  message(STATUS "${VARNAME}: ${${VARNAME}}")
endfunction()
################################

project(pyvicon_datastream_wrapper
        VERSION "0.1"
)

set (CMAKE_CXX_STANDARD 14)


# Add Boost Lib Sources
set(BOOST_INCLUDE_LIBRARIES asio system thread timer)
set(BOOST_ENABLE_CMAKE ON)

# Download and Extract the Boost Library from GitHub
message(STATUS "Downloading and extracting Boost Library Sources. This will take some time...")
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.81.0/boost-1.81.0.7z
    USES_TERMINAL_DOWNLOAD TRUE
    GIT_PROGRESS TRUE
    DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)


#find_package(Boost 1.5 COMPONENTS system thread timer REQUIRED)
find_package(PythonExtensions REQUIRED)

include(GNUInstallDirs)


#set(default_build_type "Release")
#if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
#  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
#  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
#      STRING "Choose the type of build." FORCE)
#endif()


# Declare a cpp library
add_library(ViconDataStreamSDK_CPP SHARED
  # ViconCGStreamClient
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconCGStreamClient/CGStreamReaderWriter.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconCGStreamClient/ViconCGStreamBayer.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconCGStreamClient/ViconCGStreamClient.cpp
  
  # ViconCGStreamClientSDK
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconCGStreamClientSDK/CGClient.cpp
  
  # ViconDataStreamSDK_CPP
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDK_CPP/DataStreamClient.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDK_CPP/DataStreamRetimingClient.cpp
  
  # ViconDataStreamSDKCore
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCore/CoreClient.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCore/RetimerUtils.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCore/RetimingClient.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCore/CoreClientTimingLog.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCore/RetimingCore.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCore/SegmentPoseReader.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCore/WirelessConfiguration.cpp
  
  # ViconDataStreamSDKCoreUtils
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCoreUtils/AxisMapping.cpp
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDKCoreUtils/ClientUtils.cpp
  
  # StreamCommon
  ${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/StreamCommon/CGStreamAsyncReaderWriter.cpp
)

target_include_directories(ViconDataStreamSDK_CPP PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Boost Header Libraries
target_include_directories(ViconDataStreamSDK_CPP PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/_deps/boost-src/libs/asio/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/_deps/boost-src/libs/align/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/_deps/boost-src/libs/math/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/_deps/boost-src/libs/format/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/_deps/boost-src/libs/filesystem/include>
)


target_link_libraries(ViconDataStreamSDK_CPP PRIVATE
  Boost::system
  Boost::thread
  Boost::timer
  pthread
)

# All users of this library will need at least C++14
#target_compile_features(ViconDataStreamSDK_CPP PUBLIC cxx_std_14)
#target_compile_options(ViconDataStreamSDK_CPP PRIVATE -Wno-unknown-pragmas -Wno-unused-function -Wno-unused-but-set-variable)


# Standard installation subdirs for the C++ library are used. The files will end
# up in the specified subdirectories under the Python package root. For example,
# "<python package prefix>/hello/lib/" if the destination is "lib/".
#
# Installing the objects in the package provides encapsulation and will become
# important later for binary redistribution reasons.
install(
  TARGETS ViconDataStreamSDK_CPP
  EXPORT ViconDataStreamSDK_CPPTargets
  LIBRARY DESTINATION pyvicon_datastream/${CMAKE_INSTALL_LIBDIR}
)


# The CMake package config and target files are installed under the Python
# package root. This is necessary to ensure that all the relative paths in the
# helloTargets.cmake resolve correctly. It also provides encapsulation.
#
# The actual path used must be selected so that consuming projects can locate it
# via `find_package`. To support finding CMake packages in the Python package
# prefix, using `find_package`s default search path of
# `<prefix>/<name>/share/<name>*/cmake/` is reasonable. Adding the Python
# package installation prefix to CMAKE_PREFIX_PATH in combination with this path
# will allow `find_package` to find this package and any other package installed
# via a Python package if the CMake and Python packages are named the same.

#set(PYVICON_CMAKE_PACKAGE_INSTALL_SUBDIR "share/pyvicon_cfunc/cmake")
#
#install(
# EXPORT ViconDataStreamSDK_CPPTargets
# NAMESPACE ViconDataStreamSDK_CPP::
# DESTINATION ${PYVICON_CMAKE_PACKAGE_INSTALL_SUBDIR}
#)
#
#include(CMakePackageConfigHelpers)
#
#write_basic_package_version_file(
# pyvicon_cfuncConfigVersion.cmake
# VERSION ${PROJECT_VERSION}
# COMPATIBILITY SameMinorVersion
#)
#
#configure_package_config_file(
# "${PROJECT_SOURCE_DIR}/cmake/pyvicon_cfuncConfig.cmake.in" pyvicon_cfuncConfig.cmake
# INSTALL_DESTINATION ${PYVICON_CMAKE_PACKAGE_INSTALL_SUBDIR}
#)
#
#install(FILES "${PROJECT_BINARY_DIR}/pyvicon_cfuncConfig.cmake"
#             "${PROJECT_BINARY_DIR}/pyvicon_cfuncConfigVersion.cmake"
#       DESTINATION ${PYVICON_CMAKE_PACKAGE_INSTALL_SUBDIR})



# We are using the SKBUILD variable, which is defined when scikit-build is
# running the CMake build, to control building the Python wrapper. This allows
# the C++ project to be installed, standalone, when using the standard CMake
# build flow.
if(DEFINED SKBUILD)

  # prevent an unused variable warning
  set(ignoreMe "${SKBUILD}")


  add_library(_pyvicon_datastream_wrapper MODULE 
    ${PROJECT_SOURCE_DIR}/pyvicon_datastream/pyvicon_datastream_wrapper.cpp
  )

  target_include_directories(_pyvicon_datastream_wrapper PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib_src/vicondatastream-1.11.0/Vicon/CrossMarket/DataStream/ViconDataStreamSDK_CPP>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

  target_link_libraries(_pyvicon_datastream_wrapper
    ViconDataStreamSDK_CPP
  )

  python_extension_module(_pyvicon_datastream_wrapper)


  # Installing the extension module to the root of the package
  install(TARGETS _pyvicon_datastream_wrapper LIBRARY DESTINATION pyvicon_datastream)


  # The extension module must load the hello library as a dependency when the
  # extension module is loaded. The easiest way to locate the hello library is
  # via RPATH. Absolute RPATHs are possible, but they make the resulting
  # binaries not redistributable to other Python installations (conda is broke,
  # wheel reuse is broke, and more!).
  #
  # Placing the hello library in the package and using relative RPATHs that
  # doesn't point outside of the package means that the built package is
  # relocatable. This allows for safe binary redistribution.
  if(APPLE)
    set_target_properties(
      _pyvicon_datastream_wrapper PROPERTIES INSTALL_RPATH "@loader_path/${CMAKE_INSTALL_LIBDIR}")
  else()
    set_target_properties(_pyvicon_datastream_wrapper PROPERTIES INSTALL_RPATH
                                            "$ORIGIN/${CMAKE_INSTALL_LIBDIR}")
  endif()

endif()


PRINT_VAR("APPLE")
PRINT_VAR("SKBUILD_DIR")
PRINT_VAR("PROJECT_SOURCE_DIR")
PRINT_VAR("CMAKE_INSTALL_INCLUDEDIR")
PRINT_VAR("CMAKE_INSTALL_LIBDIR")
PRINT_VAR("PYVICON_CMAKE_PACKAGE_INSTALL_SUBDIR")


PRINT_VAR("CMAKE_CURRENT_BINARY_DIR")
PRINT_VAR("CMAKE_SOURCE_DIR")


#python_extension_module(_pyvicon_datastream_wrapper)
#install(TARGETS _pyvicon_datastream_wrapper LIBRARY DESTINATION pyvicon)
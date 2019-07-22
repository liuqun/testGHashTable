cmake_minimum_required(VERSION 3.13.4)
project(MyDemoProject LANGUAGES C)

aux_source_directory(src my_demo_SOURCES)
add_executable(my_demo_prog ${my_demo_SOURCES})
set_property(TARGET my_demo_prog PROPERTY C_STANDARD 11)

if (NOT DEFINED OPENSSL_ROOT_DIR)
  set(OPENSSL_ROOT_DIR /usr/local)
  message(STATUS "Searching for OpenSSL development files from: " ${OPENSSL_ROOT_DIR})
endif ()
find_package(OpenSSL 1.1)
if (!OpenSSL_FOUND)
  message(WARNING "Try: sudo apt install libssl-dev")
  message(FATAL_ERROR "OpenSSL are required but not found!")
endif ()
message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
message(STATUS "Using include dir ${OPENSSL_INCLUDE_DIR}")
message(STATUS "Using libssl ${OPENSSL_SSL_LIBRARY}")
message(STATUS "Using libcrypto ${OPENSSL_CRYPTO_LIBRARY}")
#######################################################
find_package(PkgConfig 0.29.1 REQUIRED)
if (!PkgConfig_FOUND)
  message(FATAL_ERROR "pkg-config are required but not found!")
  return()
endif ()
#######################################################
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
if (!GLIB2_FOUND)
  message(FATAL_ERROR "GNU glib2 development files are required but not found!")
  message(WARNING "Try: sudo apt-get install libglib2.0-dev")
  return()
endif ()
find_library(GLIB2_FULL_PATH
  NAMES glib-2.0
  HINTS ${GLIB2_LIBDIR} ${GLIB2_LIBRARY_DIRS}
)
message(STATUS "Using include dir ${GLIB2_INCLUDE_DIRS}")
message(STATUS "Using ${GLIB2_FULL_PATH}")
#######################################################
target_include_directories(my_demo_prog PRIVATE
  ${OPENSSL_INCLUDE_DIR}
  ${GLIB2_INCLUDE_DIRS}
)
target_link_libraries(my_demo_prog PRIVATE
  ${OPENSSL_LIBRARIES}
  ${GLIB2_FULL_PATH}
)

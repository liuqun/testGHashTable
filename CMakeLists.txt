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
target_include_directories(my_demo_prog PRIVATE
  ${OPENSSL_INCLUDE_DIR}
)
target_link_libraries(my_demo_prog PRIVATE
  ${OPENSSL_LIBRARIES}
)

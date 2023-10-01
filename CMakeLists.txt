cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 8.8.${PATCH_VERSION})

set(CMAKE_INSTALL_PREFIX  "/home/andrey/Desktop/install-OTUS_HW2")

project(print_ip VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h @ONLY)

message(STATUS "PROJECT_NAME=${PROJECT_NAME}")


add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
#install(FILES ip_filter.tsv DESTINATION data)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)


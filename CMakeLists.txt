cmake_minimum_required(VERSION 3.28)
project(C3PO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source file of the standard library module ("import std;"), shipped with GCC >= 15.
execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=include/c++/bits/std.cc
        OUTPUT_VARIABLE STD_MODULE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
file(REAL_PATH "${STD_MODULE}" STD_MODULE)
cmake_path(GET STD_MODULE PARENT_PATH STD_MODULE_DIR)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE MODULE_INTERFACES CONFIGURE_DEPENDS src/*.cppm)

add_executable(C3PO ${SOURCES})
find_package(asio CONFIG REQUIRED)

target_link_libraries(C3PO PRIVATE asio::asio)

if(WIN32)
    target_link_libraries(C3PO PRIVATE ws2_32 mswsock)
    target_compile_definitions(C3PO PRIVATE _WIN32_WINNT=0x0A00)
endif()

target_sources(C3PO PRIVATE
        FILE_SET CXX_MODULES
        BASE_DIRS src "${STD_MODULE_DIR}"
        FILES ${MODULE_INTERFACES} "${STD_MODULE}"
)
# --allow-multiple-definition: MinGW GCC emits standard library symbols in several
# module units; without it the link fails with duplicate definitions.
target_link_options(C3PO PRIVATE -static-libgcc -static-libstdc++ -Wl,--allow-multiple-definition)


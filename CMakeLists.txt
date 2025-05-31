cmake_minimum_required(VERSION 3.16)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

# SFML install path
set(SFML_DIR "C:/SFML-3.0")

# Include headers
include_directories(
    "${SFML_DIR}/include"
    "${CMAKE_SOURCE_DIR}/header"
)

# Link SFML libraries
link_directories("${SFML_DIR}/lib")

# Automatically add all .cpp files from src/
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Create executable from all source files
add_executable(Chess ${SRC_FILES})

# Link SFML 3.0 libraries
target_link_libraries(Chess
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy assets folder to output directory
add_custom_command(TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:Chess>/assets
)

# Optionally copy required DLLs from SFML and MinGW
add_custom_command(TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_DIR}/bin/sfml-graphics-3.dll"
        "${SFML_DIR}/bin/sfml-window-3.dll"
        "${SFML_DIR}/bin/sfml-system-3.dll"
        "C:/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-18.1.8-mingw-w64ucrt-12.0.0-r1/mingw64/bin/libstdc++-6.dll"
        "C:/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-18.1.8-mingw-w64ucrt-12.0.0-r1/mingw64/bin/libwinpthread-1.dll"
        "C:/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-18.1.8-mingw-w64ucrt-12.0.0-r1/mingw64/bin/libgcc_s_seh-1.dll"
        $<TARGET_FILE_DIR:Chess>
)

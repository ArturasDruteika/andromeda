cmake_minimum_required(VERSION 3.24)

project(andromeda)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prevent GLFW from adding its development files to the install target.
set(GLFW_INSTALL OFF CACHE BOOL "Disable GLFW installation" FORCE)

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    # All files that are not compiled.
    set(CMAKE_ASSETS_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/bin")
    set(CMAKE_ASSETS_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/lib")
endif()

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}")

add_subdirectory(andromeda)
add_subdirectory(examples)

# --- Install Rules ---
install(
    DIRECTORY "${CMAKE_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/"
    DESTINATION "."
    COMPONENT runtime

    FILE_PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE

    FILES_MATCHING
        PATTERN "*"
        PATTERN "*.a" EXCLUDE
        PATTERN "*.lib" EXCLUDE
        PATTERN "*.exp" EXCLUDE
        PATTERN "*.pdb" EXCLUDE
)
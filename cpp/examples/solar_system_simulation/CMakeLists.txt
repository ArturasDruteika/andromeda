cmake_minimum_required(VERSION 3.24)

project(solar_system_simulation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        ANDROMEDA_API_USE_DLL
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        math
        api
        space
        platform
        engine
        application
        spdlog::spdlog
)

add_dependencies(${PROJECT_NAME}
    math
    space
    platform
    engine
    application
)

if(MSVC)
    file(TO_CMAKE_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/" exe_dir)

    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${exe_dir}"
    )
else()
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY
                "${CMAKE_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/bin"
    )
endif()

# ---------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------

set(EXAMPLE_INSTALL_DIR "${PROJECT_NAME}")

# Executable
install(
    PROGRAMS "$<TARGET_FILE:${PROJECT_NAME}>"
    DESTINATION "${EXAMPLE_INSTALL_DIR}/bin"
    COMPONENT runtime
)

# Shared libraries
install(
    DIRECTORY "${CMAKE_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/lib/"
    DESTINATION "${EXAMPLE_INSTALL_DIR}/lib"
    COMPONENT runtime
    FILES_MATCHING
        PATTERN "*.so"
        PATTERN "*.so.*"
        PATTERN "*.dll"
        PATTERN "*.dylib"
)

# Resources
install(
    DIRECTORY "${CMAKE_BINARY_DIR}/$<LOWER_CASE:$<CONFIG>>/res/"
    DESTINATION "${EXAMPLE_INSTALL_DIR}/res"
    COMPONENT runtime
)
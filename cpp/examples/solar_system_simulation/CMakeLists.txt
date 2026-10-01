cmake_minimum_required(VERSION 3.24)

project(solar_system_simulation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        ANDROMEDA_API_USE_DLL
)

# Ensure engine is linked
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        # precompiled_headers
        andromeda::math
        andromeda::api
        andromeda::space
        andromeda::platform
        andromeda::engine
        andromeda::application
        spdlog::spdlog
)

# Ensure Example waits for engine to build
add_dependencies(${PROJECT_NAME}
    andromeda::math
    andromeda::space
    andromeda::platform
    andromeda::engine
    andromeda::application
)

# Set working directory only for Visual Studio
if(MSVC)
    file(TO_CMAKE_PATH $<TARGET_FILE_DIR:${PROJECT_NAME}>// exe_dir)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY ${exe_dir}
    )
else()
    set_target_properties(${PROJECT_NAME}
    PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin"
    )
endif()

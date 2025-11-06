cmake_minimum_required(VERSION 3.10)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(SOURCES
    main.cpp
    render/Renderer.cpp
)

add_executable(raytracer ${SOURCES})

target_include_directories(raytracer PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/render
    ${CMAKE_SOURCE_DIR}/scene
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/objects
    ${CMAKE_SOURCE_DIR}/stb
)

find_package(nlohmann_json 3.2.0 QUIET)
if(nlohmann_json_FOUND)
    target_link_libraries(raytracer PRIVATE nlohmann_json::nlohmann_json)
else()
    message(WARNING "nlohmann_json non trouvé — assurez-vous qu'il est installé (apt install nlohmann-json3-dev)")
endif()

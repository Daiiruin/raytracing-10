cmake_minimum_required(VERSION 3.16)
project(raytracer LANGUAGES C CXX)

# ---- Langage / options -------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings utiles
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Arborescence de sorties (plus propre) ----------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   # exécutables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   # .so/.dylib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   # .a

# ---- Exécutable principal ----------------------------------------------------
add_executable(raytracer
    src/main.cpp
    src/tracer.cpp
)

# ---- Dossiers d'include ------------------------------------------------------
# 1) tes nouveaux headers refacto: includes/rt/*.hpp
# 2) anciens headers: Color.hpp / Image.hpp (rayimage) + raymath
target_include_directories(raytracer PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/includes"
    "${PROJECT_SOURCE_DIR}/src/rayimage"
    "${PROJECT_SOURCE_DIR}/src/raymath"
)

# ---- Sous-projets (librairies) ----------------------------------------------
add_subdirectory(src/raymath)
add_subdirectory(src/rayimage)
add_subdirectory(src/lodepng)

target_link_libraries(raytracer PUBLIC
    raymath
    rayimage
    lodepng
)

# ---- Install (optionnel) -----------------------------------------------------
install(TARGETS raytracer RUNTIME DESTINATION bin)

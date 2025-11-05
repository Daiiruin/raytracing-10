cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclut le dossier include/ pour les fichiers .h
include_directories(${CMAKE_SOURCE_DIR}/include)

# Liste tous les fichiers sources
set(SOURCES
    src/Camera.cpp
    src/Material.cpp
    src/Plane.cpp
    src/Ray.cpp
    src/RayTracer.cpp
    src/Scene.cpp
    src/Sphere.cpp
    src/Vec3.cpp
    main.cpp
)

# Crée l’exécutable
add_executable(RayTracer ${SOURCES})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)
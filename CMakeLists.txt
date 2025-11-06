cmake_minimum_required(VERSION 3.10)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Liste des fichiers sources
set(SOURCES
    main.cpp
    
)

# Création de l'exécutable
add_executable(raytracer ${SOURCES})

# Inclure le dossier core/ pour trouver Vec3.hpp
target_include_directories(raytracer PRIVATE
    ${CMAKE_SOURCE_DIR}/core
)

# Essayer de trouver nlohmann_json (si installé via apt)
find_package(nlohmann_json 3.2.0 QUIET)

if(nlohmann_json_FOUND)
    target_link_libraries(raytracer PRIVATE nlohmann_json::nlohmann_json)
else()
    message(WARNING " nlohmann_json non trouvé — installez-le avec : sudo apt install nlohmann-json3-dev")
endif()

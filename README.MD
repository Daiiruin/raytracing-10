Instruction de lancement du container

1. Construire l'image Docker :

    docker-compose -f .devcontainer/docker-compose.yml build

2. Lancer le conteneur :

    docker-compose -f .devcontainer/docker-compose.yml up -d

3. Accéder au conteneur :

    docker-compose -f .devcontainer/docker-compose.yml exec vscode-raytracer-sample bash


Une fois dans le container 

# Créer le dossier build s'il n'existe pas

mkdir -p build

# Aller dans le repertoire build
cd build

# Générer les fichiers de build avec CMake
cmake ..

# Compiler
make

# Exécuter le raytracer
./raytracer ../scene.json

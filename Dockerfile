# Utilise une image de base avec CMake et GCC
FROM gcc:latest

RUN apt-get update && \
    apt-get install -y cmake git

RUN    apt install -y libxrandr-dev libxinerama-dev libxcursor-dev \
    libgl1-mesa-dev \
    libudev-dev \
    libopenal-dev libvorbis-dev \
    libsndfile1-dev \
    libsfml-dev \
    build-essential 

# Définit le répertoire de travail dans l'image
WORKDIR /app

# Copie les fichiers CMakeLists.txt et le reste du code source
COPY CMakeLists.txt .
COPY src/ ./src
COPY snappy/ ./snappy
COPY SFML/ ./SFML

# Crée un répertoire pour les fichiers générés par CMake
RUN mkdir build

# Se place dans le répertoire de build
WORKDIR /app/build

# Exécute CMake pour générer les fichiers de build
RUN cmake ..

# Compile le projet
RUN make rtype-server

# Expose le port si nécessaire
EXPOSE 4242

# Commande de démarrage
CMD ["./rtype-server"]

# Dockerfile
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    cmake g++ libxerces-c-dev libexpat-dev \
    python3 python3-pip git wget \
    libx11-dev libxmu-dev libgl1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Geant4 (this takes a while)
RUN wget https://gitlab.cern.ch/geant4/geant4/-/archive/v11.2.0/geant4-v11.2.0.tar.gz \
    && tar -xzf geant4-v11.2.0.tar.gz \
    && mkdir geant4-build && cd geant4-build \
    && cmake ../geant4-v11.2.0 \
        -DGEANT4_INSTALL_DATA=ON \
        -DGEANT4_USE_OPENGL_X11=OFF \
        -DGEANT4_USE_QT=OFF \
        -DGEANT4_BUILD_MULTITHREADED=OFF \
        -DCMAKE_INSTALL_PREFIX=/usr/local/geant4 \
    && make -j$(nproc) && make install \
    && cd .. && rm -rf geant4-v11.2.0* geant4-build

# Source Geant4 environment
ENV G4ENSDFSTATEDATA=/usr/local/geant4/share/Geant4/data/G4ENSDFSTATE2.3
# (add other G4 data paths as needed)
ENV PATH=/usr/local/geant4/bin:$PATH

# Copy your app
WORKDIR /app
COPY . .

# Build the Geant4 simulation
RUN . /usr/local/geant4/bin/geant4.sh && \
    mkdir -p build && cd build && \
    cmake .. && make -j$(nproc)

# Install Python dependencies
RUN pip3 install flask

EXPOSE 5000
CMD ["python3", "src/app.py"]

# Use Ubuntu 20.04 — GCC 9 is compatible with Geant4 v10.2.3
# The ROOT project image based on Ubuntu 20.04
FROM rootproject/root:6.26.14-ubuntu20.04
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    cmake g++ gcc git wget \
    libxerces-c-dev libexpat-dev \
    libx11-dev libxmu-dev libxi-dev \
    libglu1-mesa-dev libgl1-mesa-dev \
    python3 python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Install Geant4 v10.2.3
RUN mkdir -p /geant4/src && \
    git clone https://gitlab.cern.ch/geant4/geant4.git /geant4/src && \
    cd /geant4/src && git checkout v10.2.3 && \
    mkdir /geant4/build /geant4/install && \
    cmake -B/geant4/build -S/geant4/src \
        -DCMAKE_INSTALL_PREFIX=/geant4/install \
        -DCMAKE_BUILD_TYPE=RelWithDebInfo \
        -DGEANT4_USE_GDML=ON \
        -DGEANT4_BUILD_MULTITHREADED=OFF \
        -DGEANT4_INSTALL_EXAMPLES=OFF \
        -DGEANT4_INSTALL_DATA=ON \
        -DGEANT4_USE_SYSTEM_EXPAT=OFF \
        -DGEANT4_BUILD_TLS_MODEL=auto \
        -DGEANT4_USE_QT=OFF \
        -DGEANT4_USE_OPENGL_X11=OFF \
    && cmake --build /geant4/build --target install -j$(nproc) && \
    rm -rf /geant4/src /geant4/build

ENV G4INSTALL=/geant4/install
ENV G4COMP=/geant4/install/lib/Geant4-10.2.3
ENV CMAKE_PREFIX_PATH=$G4COMP
ENV PATH=$G4INSTALL/bin:$PATH
ENV LD_LIBRARY_PATH=$G4INSTALL/lib:$LD_LIBRARY_PATH

# Copy app source
WORKDIR /app
COPY . .

# Build the Geant4 simulation
RUN /bin/bash -c " \
    . /geant4/install/bin/geant4.sh && \
    . /opt/root/bin/thisroot.sh && \
    mkdir -p build && cd build && \
    cmake -DGeant4_DIR=/geant4/install/lib/Geant4-10.2.3 \
          -DGEANT4_BUILD_MULTITHREADED=OFF \
          .. && \
    make -j$(nproc) \
"

# Install Flask
RUN pip3 install flask

EXPOSE 5000

CMD ["/bin/bash", "-c", \
    ". /geant4/install/bin/geant4.sh && \
     . /opt/root/bin/thisroot.sh && \
     cd /app/build && python3 web.py"]

FROM ubuntu:latest
LABEL maintainer="djordje.trajkovic@gmail.com"
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="Europe/Belgrade"
RUN echo 'root:root' | chpasswd; \
    useradd -s /bin/bash -d /home/djordje -m -U -G sudo djordje && echo 'djordje:djordje' | chpasswd; \
    apt update; \
    apt install -y build-essential; \
    apt install -y sudo; \
    apt install -y cmake; \
    apt install -y tzdata; \
    apt install -y git; \
    git config --global user.name "djordjetrajkovic"; \
    git config --global user.email "djordje.trajkovic@gmail.com"; \
    apt install -y cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev; \
    git clone -q https://github.com/opencv/opencv.git /home/djordje/opencv_build/opencv; \
    git clone -q https://github.com/opencv/opencv_contrib.git /home/djordje/opencv_build/opencv_contrib;
WORKDIR "/home/djordje/opencv_build/opencv/build"
RUN cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=/home/djordje/opencv_build/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON ..; \
    make -j4 && make install
USER djordje:djordje
ENV HOME /home/djordje
COPY . /home/djordje/Project/ResistorColorCode
WORKDIR "/home/djordje/Project/ResistorColorCode"
ENTRYPOINT [ "/bin/bash" ]
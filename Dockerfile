FROM ubuntu:latest
LABEL maintainer="djordje.trajkovic@gmail.com"
ARG DEBIAN_FRONTEND=noninteractive
ARG user=djordje 
ARG git_user_name=djordjetrajkovic
ARG git_email=djordje.trajkovic@gmail.com
ENV TZ="Europe/Belgrade"
ENV LD_LIBRARY_PATH="/usr/local/lib"
RUN echo 'root:root' | chpasswd; \
    useradd -s /bin/bash -d /home/${user} -m -U -G sudo ${user};
WORKDIR /home
RUN echo "${user}:${user}" > shadow.txt; \
    chpasswd < shadow.txt; \
    rm shadow.txt; \
    apt update; \
    apt install -y build-essential; \
    apt install -y sudo; \
    apt install -y cmake; \
    apt install -y tzdata; \
    apt install -y git; \
    git config --global user.name ${git_user_name}; \
    git config --global user.email ${git_email}; \
    apt install -y cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev; \
    git clone -q https://github.com/opencv/opencv.git /home/${user}/opencv_build/opencv; \
    git clone -q https://github.com/opencv/opencv_contrib.git /home/${user}/opencv_build/opencv_contrib; \
    apt install -y libboost-all-dev
    apt install -y gdb
WORKDIR "/home/${user}/opencv_build/opencv/build"
RUN cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_PC_FILE_NAME=opencv.pc \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=/home/${user}/opencv_build/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON ..; \
    make -j4 && make install
COPY . /home/${user}/Project/ResistorColorCode
RUN chown -R ${user}:${user} /home/${user}/Project
USER ${user}:${user}
ENV HOME /home/${user}
WORKDIR "/home/${user}/Project/ResistorColorCode"
ENTRYPOINT [ "/bin/bash" ]
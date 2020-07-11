FROM ubuntu:latest
LABEL maintainer="djordje.trajkovic@gmail.com"
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="Europe/Belgrade"
RUN echo 'root:root' | chpasswd; \
    apt update; \
    apt install -y build-essential; \
    apt install -y sudo; \
    apt install -y cmake; \
    apt install -y tzdata; \
    apt install -y git; \
    git config --global user.name "djordjetrajkovic"; \
    git config --global user.email "djordje.trajkovic@gmail.com"; \
    apt install -y libopencv-dev python3-opencv;   \
    useradd -s /bin/bash -d /home/djordje -m -U -G sudo djordje && echo 'djordje:djordje' | chpasswd;
USER djordje:djordje
ENV HOME /home/djordje
WORKDIR "/home/djordje/Project/ResistorColorCode"
ENTRYPOINT [ "/bin/bash" ]
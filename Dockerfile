FROM ubuntu:latest
LABEL maintainer="djordje.trajkovic@gmail.com"
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="Europe/Belgrade"
RUN apt update; \
    apt -y install sudo; \
    apt -y install tzdata; \
    apt install -y git; \
    git config --global user.name "djordjetrajkovic"; \
    git config --global user.email "djordje.trajkovic@gmail.com"; \
    apt install -y libopencv-dev python3-opencv;   \
    useradd -s /bin/bash -d /home/djordje -m -G sudo djordje && echo 'djordje:djordje' | chpasswd; \
    echo 'root:root' | chpasswd;
USER djordje:djordje
WORKDIR "/home/djordje/Project/ResistorColorCode"
ENTRYPOINT [ "/bin/bash" ]
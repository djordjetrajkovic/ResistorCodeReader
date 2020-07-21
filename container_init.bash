#!/bin/bash
# This script initializes docker container for OpenCV project.

CONF_SRC=/home/djordje/Projects/ResistorCodeReader
CONF_DST=/home/djordje/Project/ResistorColorCode

docker run -t \
    --name resistorcolorcode \
    --hostname "rcc-project" \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -e DISPLAY=unix$DISPLAY \
djordjetrajkovic/resistorcolorcodeimg
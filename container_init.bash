#!/bin/bash
# This script initializes docker container for OpenCV project.

CONF_SRC=/home/djordje/Projects/ResistorCodeReader
CONF_DST=/home/djordje/Project/ResistorColorCode

docker run -t \
    --name resistorcolorcode \
    --hostname "rcc-project" \
djordjetrajkovic/opencv:latest
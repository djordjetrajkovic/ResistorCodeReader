#!/bin/bash
# This script initializes docker container for OpenCV project.

CONF_SRC=/home/djordje/Projects/ResistorCodeReader
CONF_DST=/home/djordje/Project/ResistorColorCode

docker run -t \
    --name resistorcolorcode \
    --mount type=bind,src=${CONF_SRC},dst=${CONF_DST} \
    --hostname "rcc-project" \
djordjetrajkovic/rccimg
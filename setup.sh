#!/bin/bash

set -e

BIN_NAME="ipspoon"
SRC="main.c"
INSTALL_PATH="/usr/local/bin/$BIN_NAME"

if [ ! -f "$SRC" ]; then
    echo "Source file not found!"
    exit 1
fi

if [ ! -f "Makefile" ]; then
    echo "Makefile not found!"
    exit 1
fi

make
echo "Compiled Successfully."

sudo mv -f "$BIN_NAME" "$INSTALL_PATH"
sudo chmod +x "$INSTALL_PATH"

echo "Done setup!"
echo "Try: ipspoon -h example.com"

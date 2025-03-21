#!/bin/bash

set -e

BIN_NAME="ipspoon"
SRC="main.c"
INSTALL_PATH="/usr/local/bin/$BIN_NAME"

if [ ! -f "$SRC" ]; then
    echo "Source file not found!"
    exit 1
fi

gcc -o "$BIN_NAME" "$SRC"
echo "Compiled Successfully."

mv -i "$BIN_NAME" "$INSTALL_PATH"
sudo chmod +x "$INSTALL_PATH"

echo "Done setup!"
echo "Try: ipspoon -h example.com"

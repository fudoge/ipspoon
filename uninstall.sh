#!/bin/bash

set -e

BIN=ipspoon
INSTALLED_PATH=$(command -v "$BIN" || true)

if [ -z "$INSTALLED_PATH" ]; then
    echo "$BIN not found"
    exit 1
fi

echo "Removing $BIN at $INSTALLED_PATH"
sudo rm -f "$INSTALLED_PATH"
echo "Uninstalled $BIN"

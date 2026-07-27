#!/bin/bash
# run-ponytail.sh
# Wrapper to execute Ponytail for code auditing

TARGET_DIR="${1:-.}"
echo "Running Ponytail audit on $TARGET_DIR..."

cd /home/$USER/.openclaw/workspace/scripts/ponytail
./ponytail.sh "$TARGET_DIR" 

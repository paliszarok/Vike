#!/bin/bash
if [ -f build/Vike ]; then
  rm build/Vike
fi
if g++ src/*.cpp -o build/Vike -Wall -O2 -L /media/bence/.../Dev/ExCpp -L /home/bence/Dev/raylib -lraylib; then
  chmod +x build/Vike
  read -p "Build completed!"
else
  read -p "Build failed!"
fi

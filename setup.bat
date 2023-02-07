@echo off
git submodule update --init
cmake -S . -B build/
PAUSE

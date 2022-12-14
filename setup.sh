#!/bin/bash

git submodule update --init
cmake -S . -B build/

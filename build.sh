#!/bin/bash
g++ Engine/*.cpp *.cpp -o game -IEngine
if [ $? -eq 0 ]; then
    echo "✓ Build successful! Run with: ./game"
else
    echo "✗ Build failed"
    exit 1
fi
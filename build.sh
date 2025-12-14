#!/bin/bash

# Compile ImGui
echo "Compiling ImGui..."
g++ -c libs/imgui/imgui.cpp -o libs/imgui/imgui.o -Ilibs/imgui
g++ -c libs/imgui/imgui_draw.cpp -o libs/imgui/imgui_draw.o -Ilibs/imgui
g++ -c libs/imgui/imgui_tables.cpp -o libs/imgui/imgui_tables.o -Ilibs/imgui
g++ -c libs/imgui/imgui_widgets.cpp -o libs/imgui/imgui_widgets.o -Ilibs/imgui
g++ -c libs/imgui/imgui_impl_sdl2.cpp -o libs/imgui/imgui_impl_sdl2.o -Ilibs/imgui $(sdl2-config --cflags)
g++ -c libs/imgui/imgui_impl_sdlrenderer2.cpp -o libs/imgui/imgui_impl_sdlrenderer2.o -Ilibs/imgui $(sdl2-config --cflags)

# Compile Engine
echo "Compiling Engine..."
g++ -c Engine/*.cpp -IEngine

# Compile main
echo "Compiling main..."
g++ -c main.cpp -IEngine -Ilibs/imgui $(sdl2-config --cflags)

# Link everything
echo "Linking..."
g++ *.o libs/imgui/*.o -o game $(sdl2-config --libs) -framework OpenGL

if [ $? -eq 0 ]; then
    echo "✓ Build successful! Run with: ./game"
    # Clean up object files
    rm *.o libs/imgui/*.o 2>/dev/null
else
    echo "✗ Build failed"
    exit 1
fi
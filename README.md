# EL ZUZI Game Engine

 ZUZI Game Engine, is 2D game engine written in **C**.

## Build and Run Scripts

For windows and Linux support, the compile, debug and run scripts are Witten in Bash,
and the compilation and debug framework is **GCC** and **GDB**.

The default output directory "build".

```bash
#!/bin/bash

# Change to script directory
cd "$(dirname "$0")"

# Set include and lib paths
INCLUDE_PATH="./deps/include"
LIB_PATH="./deps/lib"

# Set libraries to link (omit .lib extension and use -l prefix)
LIBS="-lSDL3"

# Create build directory (with parent as needed) if it doesn't exist
mkdir -p ./build

# Compile with GCC
gcc -g -I"$INCLUDE_PATH" -L"$LIB_PATH" ./src/main.c -o ./build/mygame $LIBS

```

GCC/GDB Required commands:

| Switch Prefix | Command Switch    |
|---------------|-------------------|
| -g            | Debug Info        |
| -I            | Include Path      |
| -L            | Library Path      |
| -o            | Output Executable |
| -l            | Link libraries    |

Running the compiled files:

```bash
gdb ./build/myGame
```

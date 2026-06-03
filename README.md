# Digger
IN PROGRESS -- Project: Recreation of the Digger (1983) game. Made with c++, using SDL2.
Currently updating the algorithm for the enemies.

DIGGER GAME (SDL2 PROJECT)
==========================

This project is written in C++ using SDL2.
It is currently under development and is intended for learning purposes.

------------------------------------------------------------
REQUIREMENTS
------------------------------------------------------------

- Visual Studio 2022
- SDL2
- SDL2_image
- C++17 or newer

------------------------------------------------------------
HOW TO SET UP IN VISUAL STUDIO 2022
------------------------------------------------------------

1. Install SDL2 libraries:
   https://www.libsdl.org/download-2.0.php

2. Create a new Empty C++ Project in Visual Studio 2022.

3. Add all .cpp and .h files to the project.

------------------------------------------------------------
PROJECT SETTINGS 
------------------------------------------------------------

Go to Project → Properties:
Instructions: 
A) C/C++ → General → Additional Include Directories:
   Add:
   path_to_SDL2\include

B) Linker → General → Additional Library Directories:
   Add:
   path_to_SDL2\lib\x64

C) Linker → Input → Additional Dependencies:
   Add:
   SDL2.lib
   SDL2main.lib
   SDL2_image.lib

------------------------------------------------------------
DLL FILES (IMPORTANT)
------------------------------------------------------------

Copy these DLLs next to your .exe after building:

- SDL2.dll
- SDL2_image.dll

------------------------------------------------------------
ASSETS
------------------------------------------------------------

Make sure the "assets" folder is in the same directory as the executable.

------------------------------------------------------------
CONTROLS
------------------------------------------------------------

- Arrow keys: Move player

------------------------------------------------------------
NOTES
------------------------------------------------------------

This project is not finished and is mainly for learning:
- basic enemy algorithm for chasing
- tile-based map system
- collision and movement
- making games with c++

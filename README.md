# Game Engine

This is a basic game engine that was developed for the Game Engine I course at DePaul University.

### Features
  - 3 types of primitive shape models (cube, pyramid, diamond)
    - Each models' vertices contain position, texture coordinates, and normals
    - Created with reduced vertex index buffers
  - Multi-camera system
    - Swap between cameras with "C" key
    - Pan, zoom, and rotate camera with "W", "A", "S", "D" and arrow keys
  - Various GLSL shaders
    - Different combinations of texture, point light, and color shaders
  - Flat textures
    - Able to load TGA files to texture models
  - Write and read model files
    - Primitive models can be written to file as .azul
    - Load .azul files for better model creation performance
  - Game Objects
    - Game objects are all objects that appear on screen
    - Animate objects with affine transformations (scale, rotation, translation)
  
### Custom Libraries
The game engine uses 4 custom libraries, some of which act as wrappers for Window's Win32 operations.
  - _**Memory System**_
    - Created heap-based memory management system with block allocation and alignment selection functionality.
    - Implemented ability to track/debug leaking memory by displaying file and line of non-deallocation memory.
  - _**Math System**_
    - Developed library capable of performing matrix and vector math operations.
    - Optimized system by using Return Value Optimizations and forcing 16-byte data alignment for SIMD compatibility.
  - _**File System**_
    - Developed program to read, seek, tell, flush, and write files with native Win32 functions for improved performance.
  - _**Object System**_
    - Created tree data structure to manage hierarchically ordered objects.
    - Implemented forward and reverse iterators for easy access to objects on tree data structure.



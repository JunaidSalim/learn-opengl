# learn-opengl

This repository is a personal collection of OpenGL projects and experiments created while learning modern OpenGL and CMake. While following the book **"Learn OpenGL - Graphics Programming" by Joey de Vries** ([learnopengl.com](https://learnopengl.com/)), I also learned to use CMake for cross-platform C++ project management. This was a valuable learning experience, deepening my understanding of graphics programming, OpenGL, and build systems.

## Directory Structure

```
learn-opengl/
├── apps/                # Main application sources and entry points
│   ├── include/         # (Headers, if any)
│   └── src/             # Source code for each OpenGL concept
│       ├── 10cubes/     # Example: 10 cubes rendering
│       ├── coordinate/  # Coordinate systems
│       ├── cube/        # Cube rendering
│       ├── mov3d/       # 3D movement
│       ├── movement/    # Basic movement
│       ├── pad/         # Gamepad input
│       ├── rectangles/  # Rectangle rendering
│       ├── shaders/     # Shader class and uniform handling
│       ├── smiley/      # Textured smiley example
│       ├── temp/        # Temporary/test code
│       ├── texture/     # Texture loading and usage
│       ├── transformations/ # Transformations
│       └── triangles/   # Triangle rendering and blending
├── build/               # Build output (executables, binaries)
├── libs/                # External and internal libraries
│   ├── external_libs/   # GLAD, GLFW, GLM, stb_image
│   └── internal_libs/   # Custom shader library
├── CMakeLists.txt       # Root CMake build script
└── README.md            # Project documentation
```

## Referenced Resources

- **Book:** [Learn OpenGL - Graphics Programming](https://learnopengl.com/book/book_pdf.pdf)
- **Official Repo:** [https://github.com/JoeyDeVries/learnopengl](https://github.com/JoeyDeVries/learnopengl)

## Getting Started

### Prerequisites

- C++ compiler (GCC, MSVC, or Clang)
- [CMake](https://cmake.org/) (version 3.5 or higher)
- Git

### Clone the Repository

```sh
git clone https://github.com/JunaidSalim/learn-opengl.git
cd OpenGL_Game
```

### Build Instructions

#### Windows (MinGW or Visual Studio)

1. Create a build directory:
   ```sh
   mkdir build
   cd build
   ```
2. Generate project files with CMake:
   - For MinGW (GCC):
     ```sh
     cmake .. -G "MinGW Makefiles"
     ```
   - For Visual Studio:
     ```sh
     cmake .. -G "Visual Studio 17 2022"
     ```
3. Build the project:
   ```sh
   cmake --build .
   ```

#### Linux / macOS (Ubuntu, Debian, Fedora, macOS, etc.)

1. Install dependencies (example for Ubuntu/Debian):
   ```sh
   sudo apt-get update
   sudo apt-get install build-essential cmake git
   ```
2. Create a build directory:
   ```sh
   mkdir build
   cd build
   ```
3. Generate project files and build:
   ```sh
   cmake ..
   make
   ```

### Running the Examples

- After building, executables for each example will be found in `build/apps/<example_name>/`.
- To run an example, navigate to its directory and execute the binary. For example:
  ```sh
  cd build/apps/10cubes
  10cubes.exe
  ```
- Each folder in `apps/src/` corresponds to a different OpenGL concept or experiment.

## Contributing

This repository is for personal learning and experimentation. Feel free to explore, fork, or use the code for your own OpenGL journey!

---

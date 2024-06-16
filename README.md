# Basic C++ SDL2 Game

This project is a basic C++ [SDL2][SDL] Game.

## Dependencies

- C++ Compiler (g++, ...)
- [CMake][]
- [SDL2][SDL] library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install build-essential pkg-config cmake cmake-data libsdl2-dev
```

**Additional packages:**

- [SDL2_image][] library
- [SDL2_ttf][] library
- [SDL2_mixer][] library

```sh
sudo apt install libsdl2-image-dev libfreetype6-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

**Optional packages:**

```sh
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev
```

## Build instructions

```sh
# Before compiling the project you can check if the SDL2 libraries were correctly installed in /usr/local/lib
# There should be files with *.so extension (like `libSDL2.so`, `libSDL2_image.so`, ...)

# Go inside the projects folder
cd MyGame

# Type  `make`  in the terminal. 

make

# Run
./MyGame
```

***Note:*** If there were errors occurring during that point please

## License

Author: Marcin Basisty [@owoMarciN](https://gitlab.com/owoMarciN)

This project is distributed under the terms of the MIT license
[&lt;LICENSE&gt;](LICENSE).

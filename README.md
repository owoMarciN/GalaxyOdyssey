# Basic C++ SDL2 Game

This project is a basic C++ [SDL2][SDL] Game.

## Dependencies

- C++ Compiler (g++, ...)
- [SDL2](https://www.libsdl.org/) library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install build-essential pkg-config libsdl2-dev
```

**Additional packages:**

- [SDL2_image](https://github.com/libsdl-org/SDL_image) library
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf) library
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer) library

```sh
sudo apt install libsdl2-image-dev libfreetype6-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

**Optional packages:**

```sh
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev
```

## Contributing

```sh
# Before compiling the project you can check if the SDL2 libraries
# were correctly installed in  /usr/local/lib

# Go inside the projects folder
cd GalaxyOdyssey

# Type  `make`  in the terminal. 
make

# Run
./GalaxyOdyssey
```

***Note:*** I know there's memory leaks plaese don't hate me :'(

## License

Author: Marcin Basisty [@owoMarciN](https://github.com/owoMarciN)

This project is distributed under the terms of the MIT license
[&lt;LICENSE&gt;](https://www.mit.edu/~amini/LICENSE.md).

emcc main.c Scripts/*.c Engine/*.c -s WASM=1 --use-port=sdl3 -s USE_SDL_IMAGE=3 -s USE_SDL_TTF=3 -s INITIAL_MEMORY=64MB -s ALLOW_MEMORY_GROWTH=1 --preload-file Art --preload-file Engine --preload-file Sounds --preload-file Fonts --preload-file Scripts  -o index.html
#-s SDL3_IMAGE_FORMATS='["png"]'
#-s USE_SDL_MIXER=3 -s SDL2_MIXER_FORMATS='["wav"]'

emcc main.c -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 --preload-file art --preload-file Engine --preload-file Sounds -o main.html

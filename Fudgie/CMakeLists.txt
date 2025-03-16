cmake_minimum_required(VERSION 3.10)
project(MyGame)

set(CMAKE_C_COMPILER emcc)
set(CMAKE_CXX_COMPILER em++)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

# Add source files
file(GLOB_RECURSE SOURCES "main.c" "Engine/*.c" "Scripts/*.c")

# Add executable
add_executable(game ${SOURCES})



set(SDL3_DIR "~/Documents/repos/SDL3")
set(SDL3_IMAGE_DIR "~/Documents/repos/SDL_image")
set(SDL3_TTF_DIR "~/Documents/repos/SDL_ttf")
set(FREETYPE "~/Documents/repos/freetype")
# set(SDL3_IMAGE_LIB "~/Documents/repos/SDL_image/libSDL3_image.a")
# set(SDL3_TTF_LIB "~/Documents/repos/SDL_ttf/libSDL3_ttf.a")

# Include directories
include_directories(
    ${SDL3_DIR}/include
    ${SDL3_IMAGE_DIR}/include
    ${SDL3_TTF_DIR}/include
    ${FREETYPE}/include
)

# Link directories
link_directories(
    ${SDL3_DIR}/
    ${SDL3_IMAGE_DIR}/
    ${SDL3_TTF_DIR}/
    ${FREETYPE}/
)

# Link the libraries
# target_link_libraries(game PRIVATE SDL3 ${SDL3_IMAGE_LIB} ${SDL3_TTF_LIB})
target_link_libraries(game PRIVATE SDL3 SDL3_image SDL3_ttf freetype z)

# Enable WebAssembly and asset preloading
set_target_properties(game PROPERTIES LINK_FLAGS "-s WASM=1 -sALLOW_MEMORY_GROWTH=1 --preload-file ../Art/ --preload-file ../Fonts/")

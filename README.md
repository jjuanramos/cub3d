# 🧊 cub3D

Ray‑casting project inspired by Wolfenstein 3D, developed by [cmunoz-g](https://github.com/cmunoz-g) and [jjuanramos](https://github.com/jjuanramos). Renders a first‑person view from a 2D map using MiniLibX, with textured walls, smooth movement, and real‑time updates.


## Build and run

**Requirements:** C compiler, `make`, MiniLibX (included as a submodule), **X11** development headers, and **libbsd**.

```bash
# Clone (includes submodules like MiniLibX)
git clone --recurse-submodules https://github.com/jjuanramos/cub3d
cd cub3d

# Build
make

# Run
./cub3D path/to/map.cub
```


## Usage

* Provide a `.cub` map describing textures, colors, and layout.
* Run the binary with the path to the map file.

**Controls**

* `W` `A` `S` `D` — move forward/left/back/right
* `←` `→` — rotate view
* `ESC` — exit


## Features

* **First‑person ray casting** from a 2D grid map.
* **Textured walls** with orientation‑based textures (N/S/E/W).
* **Player movement and rotation** with collision checks.
* **Dynamic rendering**: real‑time frame updates via MiniLibX.


## Project structure

* **src/** — core logic: initialization, parsing, ray casting, rendering, input.
* **include/** — headers and shared types.
* **maps/** — sample `.cub` maps.
* **mlx/** — MiniLibX (git submodule).
* **Makefile** — build targets for debug/release and cleanup.


## Map file requirements

* **Walls (`1`)** fully enclose the traversable area.
* **Player start** exactly one of `N`, `S`, `E`, `W` marking spawn and facing.
* **Valid tokens** only `0` (empty), `1` (wall), `N`/`S`/`E`/`W` (spawn).
* **Textures** paths for N/S/E/W walls.
* **Colors** RGB for floor and ceiling.


## Implementation details

* **Initialization**: All structures and variables initialized to `NULL` or `0`.
* **Parsing**: `.cub` file parsed to extract map, textures, colors.
* **MiniLibX**: Sets up window and handles rendering/events.
* **Ray casting** (`cast_rays()`): Computes wall distances by casting rays at angle increments, using horizontal and vertical intersections, then chooses nearest hit.
* **Rendering** (`render()`, `draw_wall()`): Draws walls, floor, ceiling. Calculates texture offsets and scales textures by wall height and player distance.
* **Movement** (`hook_player_mvmt()`): Updates position/rotation, checks for collisions against walls.


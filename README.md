# 🧊 cub3D

## Overview
**cub3D** is a ray-casting project inspired by the classic Wolfenstein 3D game, developed collaboratively by [cmunoz-g](https://github.com/cmunoz-g) and [jjuanramos](https://github.com/jjuanramos). The project aims to create a first-person 3D game environment using a 2D map layout. It covers fundamental concepts like ray-casting, texture rendering and player movement, offering a framework for understanding the mechanics behind 3D game engines.

## Features
- **First-Person Perspective**: Navigate through a 3D maze rendered from a 2D map using a custom ray-casting engine.
- **Textured Walls**: Walls are rendered with distinct textures based on their orientation (North, South, East, West).
- **Player Movement and Rotation**: Smooth movement and rotation using keyboard controls. 
- **Dynamic Rendering**: Real-time rendering of the environment as the player moves and rotates within the maze.

## Project Structure
The project follows a structured flow:
1. **Initialization**: All structures and variables are initialized to `NULL` or `0`, following safe practices.
2. **Parsing**: The `.cub` map file is parsed to extract the map layout, textures, and colors.
3. **MiniLibX Initialization**: MiniLibX is used to create the game window and manage graphics.
4. **Ray-Casting Calculations**: The `cast_rays()` function calculates the distance to walls by casting rays at incremental angles. It uses both horizontal and vertical ray intersections to determine the closest wall. Each ray's intersection point and distance are then used to render the appropriate textures onto the screen.
5. **Texture Rendering**: We use `render()` to render walls, floor, and ceiling with appropriate textures based on the player's perspective. The `draw_wall()` function calculates the texture offset and scales it according to the wall height and player position, ensuring a smooth and realistic display of textures.
6. **Player actions**: The function `hook_player_mvmt()` updates the player's position based on the current movement and rotation state. Wall collisions are detected using the player's new position to prevent moving through walls.

## Installation and Execution
1. **Clone the Repository**:
    ```bash
    git clone [https://github.com/cmunoz-g/cub3d.git](https://github.com/jjuanramos/cub3d.git)
    ```
2. **Navigate to the Project Directory**:
    ```bash
    cd cub3d
    ```
3. **Compile the Program**:
    ```bash
    make
    ```
4. **Run the Game**:
    ```bash
    ./cub3D path/to/map.cub
    ```
   Replace `path/to/map.cub` with the path to your `.cub` map file.

## Map File Requirements
The game relies on a `.cub` configuration file, which must meet the following criteria:
- **Walls (`1`)**: Enclose the entire map.
- **Player Start Position**: One of `N`, `S`, `E`, `W` to indicate the player's initial position and orientation.
- **Valid Characters**: Only `0` (empty space), `1` (wall), and `N`, `S`, `E`, `W` (player start position) are allowed in the map area.
- **Texture and Color Definitions**: Paths for wall textures and RGB colors for the floor and ceiling must be specified.

## Controls
Player movement is handled through keyboard input, where the player's position is updated based on the keys pressed:
- **`W`, `A`, `S`, `D`**: Move forward, left, backward, and right, respectively.
- **Left/Right Arrows**: Rotate the player's view left or right.
- **ESC**: Exit the game.

**cub3D** offers a hands-on experience with low-level graphics programming in C, using MiniLibX for rendering and event handling. It demonstrates how to build a basic 3D game engine, covering aspects like ray-casting, collision detection, and texture mapping. By navigating through the maze and avoiding walls, users can experience a simplified version of a classic 3D game.

Enjoy navigating the maps! 😊

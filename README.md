# So_Long

So_Long is a simple 2D game project where the player (P) must collect all items (C) in the game map and reach the exit (E). The project uses the MinilibX library for rendering graphics in a window.

## Features
- **2D Graphics**: Implemented using the MinilibX library.
- **Game Objectives**:
  - The player must navigate the map, collect all items, and find the exit.
  - Invalid maps include:
    - Non-rectangular maps.
    - Maps missing a player, collectables, or an exit.
    - Unknown characters (not 0, 1, P, E, or C), will also make the map invalid.
    - Maps not enclosed by walls.
    - Maps with empty lines inside them.
    - Files without ```.ber``` extension.
  - The **floodfill** algorithm checks if the map is winnable; otherwise it's marked as invalid.
  
## How It Works
- The map is rendered using MinilibX, and the player's movements are controlled through keyboard input, either arrow keys or WASD.

## Usage
1. Compile the program:
    ```make```
2. Run the game:
    ```./so_long ./maps/<map_file.ber>```


## Game Gif
![Game Gif](https://github.com/gracaflucas/So_Long/blob/main/game.gif)

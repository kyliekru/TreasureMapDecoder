# Treasure Map Decoder

This project is a C++ program designed to create and decode a treasure map from a base image and a maze image. It leverages classes such as `treasureMap` and `decoder`, and uses a queue data structure for pathfinding and a decoding algorithm to find the solution.

## Features

- **Treasure Map Creation**: Create a treasure map by embedding a maze onto a base image.
- **Maze Rendering**: Render a maze with paths to the treasure.
- **Solution Rendering**: Decode the treasure map using a queue-based pathfinding algorithm and render the solution path through the maze.

## Usage  

**Build**: ```make```  
**Run**: ```./pa2```

## Dependencies

- Standard C++ libraries
- PNG image handling via `cs221util::PNG`

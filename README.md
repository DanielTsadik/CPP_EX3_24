# Settlers of Catan Game

## Author
**Daniel Tsadik**  
Email: [Tsadik88@gmail.com](mailto:Tsadik88@gmail.com)

---

## Table of Contents
1. [Game Rules](#game-rules)
2. [Class Hierarchy](#class-hierarchy)
3. [Libraries Used](#libraries-used)
4. [Prerequisites](#prerequisites)
5. [Installation Instructions](#installation-instructions)
6. [Compilation Instructions](#compilation-instructions)
7. [Running the Game](#running-the-game)
8. [Usage](#usage)
9. [Examples](#examples)
10. [Contributing](#contributing)
11. [License](#license)
12. [Acknowledgments](#acknowledgments)
13. [Issues and Troubleshooting](#issues-and-troubleshooting)

---

## Game Rules

This implementation follows the rules of the popular board game Settlers of Catan. The game is designed for three players, and the objective is to be the first player to reach a certain number of victory points (10 in this implementation).

1. **Setup**: The game board is initialized with a fixed configuration of 19 plots, each with a specific resource type (Mountains, Pasture, Forest, Agricultural, Hills, or Desert) and a number (2-12, except for the Desert plot). There are 54 vertices and 72 edges on the board.

2. **Initial Placement**: Each player takes turns placing two settlements and two roads on the board. Settlements must be placed on unoccupied vertices that are not adjacent to any other settlements or cities. Roads must connect a player's settlement to another unoccupied vertex.

3. **Resource Collection**: On each turn, two dice are rolled, and players with settlements or cities adjacent to plots with the corresponding number receive resources based on the plot's resource type. If a 7 is rolled, players with more than 7 cards must discard half of their resources.

4. **Development Cards**: Players can draw Development Cards from a deck, which can provide various benefits, such as additional resources, roads, or victory points. The deck consists of 14 Knights, 5 Victory Points, 2 Road Building, 2 Year of Plenty, and 2 Monopoly cards.

5. **Building**: Players can use their resources to build new settlements, cities, or roads on the board, following specific placement rules.

6. **Victory Condition**: The first player to reach 10 victory points (determined by the number of settlements, cities, and Development Cards) wins the game.

## Class Hierarchy

- `Board`: Manages the game board, including plots, vertices, edges, and players. It handles resource distribution, development card drawing, and building placement rules.
- `Plot`: Represents a plot on the board with a specific resource type, number, and vertices.
- `Vertex`: Represents a vertex on the board, which can be occupied by a settlement or city.
- `Edge`: Represents an edge on the board, which can be occupied by a road.
- `Player`: Represents a player in the game, with resources, settlements, cities, roads, and development cards.
- `DevelopmentCard`: Represents a development card with a specific type (Knight, Victory Point, Road Placement, Year of Plenty, or Monopoly).

## Libraries Used

The following libraries are used in this implementation:

- `<iostream>`: For input/output operations.
- `<vector>`: For dynamic array storage.
- `<tuple>`: For holding plot data.
- `<algorithm>`: For shuffling the development card deck.
- `<random>`: For generating random numbers for shuffling.
- `<chrono>`: For seeding the random number generator.

## Prerequisites

- C++ Compiler (e.g., GCC, Clang)
- C++ Standard Library

## Installation Instructions

1. Ensure you have a C++ compiler installed.
2. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/yourusername/settlers-of-catan.git
    cd settlers-of-catan
    ```

## Compilation Instructions

To compile the source files, use the following command:
```bash
g++ -o catan Board.cpp DevelopmentCard.cpp Edge.cpp Plot.cpp Vertex.cpp Player.cpp

Running the Game

After compilation, run the game using the following command:

bash

./catan

Usage

The game will prompt players for their moves and actions according to the game rules.
Examples

Here is an example of how the game prompts might look:

mathematica

Player 1, place your first settlement.
Enter the vertex number: 12
Player 1, place your first road.
Enter the edge number: 34

Contributing

Contributions are welcome! Please fork the repository and create a pull request with your changes. Make sure to follow the coding style guidelines and include tests for any new functionality.
License

This project is licensed under the MIT License - see the LICENSE file for details.
Acknowledgments

Thanks to the developers and community who have contributed to the libraries and tools used in this project.
Issues and Troubleshooting

If you encounter any issues, please check the issues page for existing problems or open a new issue.
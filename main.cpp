#include <iostream>
#include <stdexcept>
#include <vector>
#include "Player.hpp"
#include "Board.hpp"
#include "catan.hpp"

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Board board;
    Catan catan(p1, p2, p3);

    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer(); // should print the name of the starting player, assume it is Amit.
    board.initializeBoard();      // Initialize the board
    p1.setBoard(board);           // Set board for player 1
    p2.setBoard(board);           // Set board for player 2
    p3.setBoard(board);           // Set board for player 3

    // Distribute some initial resources for testing trades
    p1.addResource("wood", 2);
    p1.addResource("brick", 2);
    p2.addResource("wool", 1);
    p2.addResource("iron", 1);

    std::vector<std::string> places = {"Forest", "Hills"};
    std::vector<int> placesNum = {5, 6};
    p1.placeSettlement(places, placesNum, board);
    p1.placeRoad(places, placesNum, board);
    places = {"Agricultural Land", "Desert"};
    placesNum = {3, 4};
    p1.placeSettlement(places, placesNum, board);
    p1.placeRoad(places, placesNum, board);

    places = {"Mountains", "Pasture Land"};
    placesNum = {4, 9};
    p2.placeSettlement(places, placesNum, board);
    p2.placeRoad(places, placesNum, board);
    try {
        places = {"Mountains", "Pasture Land"};
        placesNum = {4, 9};
        p3.placeSettlement(places, placesNum, board); // p3 tries to place a settlement in the same location as p2.
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    places = {"Forest", "Pasture Land"};
    placesNum = {5, 9};
    p2.placeSettlement(places, placesNum, board);
    p2.placeRoad(places, placesNum, board);

    places = {"Mountains", "Pasture Land"};
    placesNum = {3, 8};
    p3.placeSettlement(places, placesNum, board);
    places = {"Agricultural Land", "Pasture Land"};
    placesNum = {3, 9};
    p3.placeSettlement(places, placesNum, board);
    p3.placeRoad(places, placesNum, board);

    // p1 has wood, bricks, and wheat, p2 has wood, ore, and wool, p3 has ore, wool, wheat.
    p1.rollDice();                                    // Let's say it's print 4. Then, p2 gets ore from the mountains.
    p1.placeRoad({"Forest", "Hills"}, {5, 6}, board); // p1 continues to build a road.
    p1.endTurn();                                     // p1 ends his turn.

    p2.rollDice(); // Let's say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.endTurn();  // p2 ends his turn.

    p3.rollDice(); // Let's say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    p3.endTurn();  // p3 ends his turn.

    try {
        p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    p1.rollDice();                       // Let's say it's print 6. Then, p1 gets bricks from the hills.
    try {
        p1.trade(p2, "wood", "brick", 1, 1); // p1 trades 1 wood for 1 brick with p2.
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    p1.endTurn();                        // p1 ends his turn.

    p2.rollDice();           // Let's say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    try {
        p2.buyDevelopmentCard(); // p2 buys a development card. Let's say it is a bonus points card.
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    p2.endTurn();            // p2 ends his turn.

    p1.printPoints();    // p1 has 2 points because it has two settlements.
    p2.printPoints();    // p2 has 3 points because it has two settlements and a bonus points card.
    p3.printPoints();    // p3 has 2 points because it has two settlements.
    catan.printWinner(); // Should print None because no player reached 10 points.

    return 0;
}

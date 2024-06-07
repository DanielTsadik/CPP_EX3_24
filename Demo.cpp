// #include <iostream>
// #include <stdexcept>
// #include <vector>
// #include "catan.hpp"
// #include "player.hpp"
// #include "board.hpp"

// int main()
// {
//     // Create players
//     Player p1("Daniel");
//     Player p2("David");
//     Player p3("Yossi");

//     // Initialize the game
//     const Board board;

//     // Create the game
//     Catan catan(p1, p2, p3);

//     try
//     {
//         // Starting of the game. Every player places two settlements and two roads.

//         catan.ChooseStartingPlayer(); // Determine starting player

//         // Player 1 places first settlements and roads
//         std::vector<std::string> places1 = {"Forest", "Hills"};
//         std::vector<int> placesNum1 = {5, 6};
//         p1.placeSettlement(places1, placesNum1, board); // Print should be: // Player 1 placed a settlement on Forest (5)
//         p1.placeRoad(places1, placesNum1, board);       // Print should be: // Player 1 placed a road between Forest (5) and Hills (6)

//         // Player 1 places second settlements and roads
//         std::vector<std::string> places2 = {"Agricultural Land", "Desert"};
//         std::vector<int> placesNum2 = {3, -1};          // Desert has no number
//         p1.placeSettlement(places2, placesNum2, board); // Print should be: // Player 1 placed a settlement on Agricultural Land (3)
//         p1.placeRoad(places2, placesNum2, board);       // Print should be: // Player 1 placed a road between Agricultural Land (3) and Desert
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     try
//     {
//         // Player 2 places first settlements and roads
//         std::vector<std::string> places3 = {"Mountains", "Pasture Land"};
//         std::vector<int> placesNum3 = {4, 9};
//         p2.placeSettlement(places3, placesNum3, board); // Print should be: // Player 2 placed a settlement on Mountains (4)
//         p2.placeRoad(places3, placesNum3, board);       // Print should be: // Player 2 placed a road between Mountains (4) and Pasture Land (9)

//         // Player 2 places second settlements and roads
//         std::vector<std::string> places4 = {"Forest", "Pasture Land"};
//         std::vector<int> placesNum4 = {5, 9};
//         p2.placeSettlement(places4, placesNum4, board); // Print should be: // Player 2 placed a settlement on Forest (5)
//         p2.placeRoad(places4, placesNum4, board);       // Print should be: // Player 2 placed a road between Forest (5) and Pasture Land (9)
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     try
//     {
//         // Player 3 places first settlements and roads
//         std::vector<std::string> places5 = {"Mountains", "Pasture Land"};
//         std::vector<int> placesNum5 = {3, 8};
//         p3.placeSettlement(places5, placesNum5, board); // Print should be: // Player 3 placed a settlement on Mountains (3)
//         p3.placeRoad(places5, placesNum5, board);       // Print should be: // Player 3 placed a road between Mountains (3) and Pasture Land (8)

//         // Player 3 places second settlements and roads
//         std::vector<std::string> places6 = {"Agricultural Land", "Pasture Land"};
//         std::vector<int> placesNum6 = {3, 9};
//         p3.placeSettlement(places6, placesNum6, board); // Print should be: // Player 3 placed a settlement on Agricultural Land (3)
//         p3.placeRoad(places6, placesNum6, board);       // Print should be: // Player 3 placed a road between Agricultural Land (3) and Pasture Land (9)
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     // Simulate a full round of the game after initial placements

//     // Roll the dice for each player
//     p1.rollDice(); // Player 1 rolls the dice and gets 5
//     // should print: // Player 1 received 1 Wood
//     p1.placeRoad({"Mountains", "Pasture Land"}, {4, 9}, &board); // Player 1 places a road between Mountains (4) and Pasture Land (9)
//     p1.endTurn();                                                // Player 1 ends their turn

//     p2.rollDice(); // Player 2 rolls the dice
//     p2.endTurn();  // Player 2 ends their turn

//     p3.rollDice(); // Player 3 rolls the dice
//     p3.endTurn();  // Player 3 ends their turn

//     try
//     {
//         p2.rollDice(); // Player 2 try to roll the dice when it's not their turn
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     p1.rollDice();                       // Player 1 rolls the dice
//     p1.trade(p2, "Brick", "Wood", 1, 1); // Player 1 trades 1 Brick for 1 Wood with Player 2
//     p1.endTurn();                        // Player 1 ends their turn

//     p2.rollDice();           // Player 2 rolls the dice
//     p2.buyDevelopmentCard(); // Player 2 buys a development card
//     p2.endTurn();            // Player 2 ends their turn

//     p3.rollDice(); // Player 3 rolls the dice
//     p3.endTurn();  // Player 3 ends their turn

//     // Continue the game...

//     return 0;
// }

/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "Board.hpp"
using namespace std;
using namespace ariel;

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    Board board = catan.getBoard(); // get the board of the game.
    vector<string> places = {"Forest", "Hills"};
    vector<int> placesNum = {5, 6};
    p1.placeSettelemnt(places, placesNum, board);
    p1.placeRoad(places, placesNum, board);
    vector<string> places = {"Agricultural Land", "Desert"};
    vector<int> placesNum = {3, 4};
    p1.placeSettelemnt(places, placesNum, board);
    p1.placeRoad(places, placesNum, board); // p1 chooses Forest, hills, Agricultural Land, Desert with numbers 5, 6, 3, 4.

    vector<string> places = {"Mountains", "Pasture Land"};
    vector<int> placesNum = {4, 9};
    p2.placeSettelemnt(places, placesNum, board);
    p2.placeRoad(places, placesNum, board);
    try
    {
        p3.placeSettelemnt(places, placesNum, board); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    vector<string> places = {"Forest", "Pasture Land"};
    vector<int> placesNum = {5, 9};
    p2.placeSettelemnt(places, placesNum, board);
    p2.placeRoad(places, placesNum, board); // p2 chooses Mountains, Pasture Land, and Forest with numbers 4, 9, 5.

    vector<string> places = {"Mountains", "Pasture Land"};
    vector<int> placesNum = {3, 8};
    p3.placeSettelemnt(places, placesNum, board);
    p3.placeRoad(places, placesNum, board);
    vector<string> places = {"Agricultural Land", "Pasture Land"};
    vector<int> placesNum = {3, 9};
    p3.placeSettelemnt(places, placesNum, board);
    p3.placeRoad(places, placesNum, board); // p3 chooses Mountains, Pasture Land, Agricultural Land, Pasture Land with numbers 3, 8, 3, 9.

    // p1 has wood,bricks, and wheat, p2 has wood, ore, and wool, p3 has ore, wool, wheat.
    p1.rollDice();                                    // Lets say it's print 4. Then, p2 gets ore from the mountations.
    p1.placeRoad({"Forest", "Hills"}, {5, 6}, board); // p1 continues to build a road.
    p1.endTurn();                                     // p1 ends his turn.

    p2.rollDice(); // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.endTurn();  // p2 ends his turn.

    p3.rollDice(); // Lets say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    p3.endTurn();  // p3 ends his turn.

    try
    {
        p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    p1.rollDice();                       // Lets say it's print 6. Then, p1 gets bricks from the hills.
    p1.trade(p2, "wood", "brick", 1, 1); // p1 trades 1 wood for 1 brick with p2.
    p1.endTurn();                        // p1 ends his turn.

    p2.rollDice();           // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.buyDevelopmentCard(); // p2 buys a development card. Lets say it is a bonus points card.
    p2.endTurn();            // p2 ends his turn.

    p1.printPoints(); // p1 has 2 points because it has two settelments.
    p2.printPoints(); // p2 has 3 points because it has two settelments and a bonus points card.
    p3.printPoints(); // p3 has 2 points because it has two settelments.

    catan.printWinner(); // Should print None because no player reached 10 points.
}

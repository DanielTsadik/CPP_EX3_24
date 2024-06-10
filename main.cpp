#include <iostream>
#include "Player.hpp"
#include "Board.hpp"

using namespace std;

int main()
{
    srand(time(0)); // use current time as seed for random generator

    Player player(1, "DANIEL");
    Player player2(2, "David");
    Player player3(3, "Yoash");

    Board board(player, player2, player3);

    // Set the initial settlements and roads
    player.placeInitialSettlementAndRoad(19, 18, board);
    player2.placeInitialSettlementAndRoad(44, 34, board);
    player3.placeInitialSettlementAndRoad(42, 43, board);
    player3.placeInitialSettlementAndRoad(13, 12, board);
    player2.placeInitialSettlementAndRoad(40, 41, board);
    player.placeInitialSettlementAndRoad(35, 24, board);
    cout << "\n"
              << endl;

    // First round: Lets go!
    player.rollDice(board);
    player.placeRoad(25, 24, board);
    player.tradeResources(board, 3, "Brick", 1, "Ore", 1);
    player.tradeResources(board, 2, "Brick", 1, "Ore", 1);
    player.getSettlements(board);
    player.placeSettlement(25, board);

    board.printWinner();

    // // player 1 tries to place a settlement although he has no resources

    // player2.rollDice(board);
    // player2.placeRoad(33, 34, board);
    // player2.placeSettlement(33, board);

    // player3.rollDice(board);
    // // player3.chooseDevelopmentCard(board);
    // player3.useKnight(board);
    // player3.tradeResources(board, 2, "Ore", 1, "Wool", 1);
    // player3.upgradeToCity(13, board);
    // // player3.chooseDevelopmentCard(board);
    // player.rollDice(board);
    // player2.rollDice(board);
    // player3.rollDice(board);
    // player3.rollDice(board);

    // player3.rollDice(board);

    // player3.rollDice(board);

    // player3.rollDice(board);
    // player3.rollDice(board);
    // player3.rollDice(board);
    // player3.rollDice(board);

    return 0;
}

#include <iostream>
#include "Player.hpp"
#include "Board.hpp"

int main()
{
    Player player(1, "DANIEL");
    Player player2(2, "David");
    Player player3(3, "Yoash");

    Board board(player, player2, player3);
    board.printBoard();
    player.placeInitialSettlementAndRoad(19, 18, board);
    // player2.placeInitialSettlementAndRoad(44, 34, board);
    // player3.placeInitialSettlementAndRoad(42, 43, board);
    // player3.placeInitialSettlementAndRoad(13, 12, board);
    // player2.placeInitialSettlementAndRoad(40, 41, board);
    player.placeInitialSettlementAndRoad(35, 24, board);

    player.placeSettlement(13, board);

    return 0;
}

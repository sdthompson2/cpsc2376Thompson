#include <iostream>
#include <vector>
#include <random>
#include <string>

// Plain enums as requested
enum Status { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };
enum Gem { DIAMOND, RUBY, EMERALD, SAPPHIRE, AMETHYST, TOPAZ, EMPTY };

class Game {
private:
    static const int BOARD_SIZE = 8;
    std::vector<std::vector<Gem>> board;
    int currentPlayer;  // 1 or 2
    int player1Score;
    int player2Score;
    int movesRemaining;
    bool gameActive;

    // Random number generator for gem creation
    std::mt19937 rng;
    std::uniform_int_distribution<int> gemDist;

    // Check for matches after a swap
    bool checkMatches(int row1, int col1, int row2, int col2);

    // Check for three or more gems in a row/column
    bool checkForMatches();

    // Remove matched gems and add score
    void removeMatches();

    // Fill empty spaces with new gems
    void fillBoard();

    // Check if there are any possible moves
    bool hasPossibleMoves();

    // Validate a move (swap)
    bool isValidMove(int row1, int col1, int row2, int col2) const;

    // Check if coordinates are adjacent
    bool isAdjacent(int row1, int col1, int row2, int col2) const;

    // Initialize the board with random gems
    void initializeBoard();


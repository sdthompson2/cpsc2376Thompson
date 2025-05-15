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

public:
    // Constructor initializes game
    Game(int moveLimit = 20);

    // Make a move (swap two adjacent gems)
    bool play(int row1, int col1, int row2, int col2);

    // Get current game status
    Status status() const;

    // Get current scores
    int getPlayer1Score() const { return player1Score; }
    int getPlayer2Score() const { return player2Score; }

    // Get current player
    int getCurrentPlayer() const { return currentPlayer; }

    // Get moves remaining
    int getMovesRemaining() const { return movesRemaining; }

    // Display the board (could be replaced with friend operator<<)
    void display() const;

    // Friend operator for streaming output
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};

// Implementation of Game constructor
Game::Game(int moveLimit) :
    currentPlayer(1),
    player1Score(0),
    player2Score(0),
    movesRemaining(moveLimit),
    gameActive(true),
    rng(std::random_device{}()),
    gemDist(0, 5) // 6 gem types
{
    initializeBoard();
}

void Game::initializeBoard() {
    // Initialize with empty board
    board = std::vector<std::vector<Gem>>(BOARD_SIZE, std::vector<Gem>(BOARD_SIZE, EMPTY));

    // Fill with random gems, avoiding initial matches
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Gem newGem;
            do {
                newGem = static_cast<Gem>(gemDist(rng));
                board[i][j] = newGem;
            } while (
                // Check for horizontal matches
                (j >= 2 && board[i][j - 1] == newGem && board[i][j - 2] == newGem) ||
                // Check for vertical matches
                (i >= 2 && board[i - 1][j] == newGem && board[i - 2][j] == newGem)
                );
        }
    }
}

bool Game::isValidMove(int row1, int col1, int row2, int col2) const {
    // Check if coordinates are within bounds
    if (row1 < 0 || row1 >= BOARD_SIZE || col1 < 0 || col1 >= BOARD_SIZE ||
        row2 < 0 || row2 >= BOARD_SIZE || col2 < 0 || col2 >= BOARD_SIZE) {
        return false;
    }

    // Check if the gems are adjacent
    if (!isAdjacent(row1, col1, row2, col2)) {
        return false;
    }

    return true;
}

bool Game::isAdjacent(int row1, int col1, int row2, int col2) const {
    // Two positions are adjacent if they differ by 1 in exactly one coordinate
    int rowDiff = abs(row1 - row2);
    int colDiff = abs(col1 - col2);

    return (rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1);
}

bool Game::play(int row1, int col1, int row2, int col2) {
    if (!gameActive || movesRemaining <= 0) {
        return false;
    }

    if (!isValidMove(row1, col1, row2, col2)) {
        return false;
    }

    // Swap gems
    std::swap(board[row1][col1], board[row2][col2]);

    // Check if swap creates a match
    if (!checkMatches(row1, col1, row2, col2)) {
        // If no match, swap back
        std::swap(board[row1][col1], board[row2][col2]);
        return false;
    }

    // Remove matched gems and add score
    removeMatches();

    // Fill empty spaces
    fillBoard();

    // Decrement moves and switch player
    movesRemaining--;
    currentPlayer = (currentPlayer == 1) ? 2 : 1;

    // Check if game should end
    if (movesRemaining <= 0 || !hasPossibleMoves()) {
        gameActive = false;
    }

    return true;
}

bool Game::checkMatches(int row1, int col1, int row2, int col2) {
    // Check if any matches are created after the swap
    // This is a simplified version - actual implementation would check for patterns
    return checkForMatches();
}

bool Game::checkForMatches() {
    // Check for horizontal and vertical matches of 3 or more
    bool foundMatch = false;

    // Check horizontal matches
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - 2; j++) {
            if (board[i][j] != EMPTY &&
                board[i][j] == board[i][j + 1] &&
                board[i][j] == board[i][j + 2]) {
                foundMatch = true;
                // In a real implementation, we'd mark these for removal
            }
        }
    }

    // Check vertical matches
    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i < BOARD_SIZE - 2; i++) {
            if (board[i][j] != EMPTY &&
                board[i][j] == board[i + 1][j] &&
                board[i][j] == board[i + 2][j]) {
                foundMatch = true;
                // In a real implementation, we'd mark these for removal
            }
        }
    }

    return foundMatch;
}

void Game::removeMatches() {
    // This is a simplified implementation
    // In a real game, we'd identify all matching gems and remove them

    // For horizontal matches
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - 2; j++) {
            if (board[i][j] != EMPTY &&
                board[i][j] == board[i][j + 1] &&
                board[i][j] == board[i][j + 2]) {

                // Add points to current player
                if (currentPlayer == 1)
                    player1Score += 3;
                else
                    player2Score += 3;

                // Remove matched gems
                board[i][j] = EMPTY;
                board[i][j + 1] = EMPTY;
                board[i][j + 2] = EMPTY;
            }
        }
    }

    // For vertical matches
    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i < BOARD_SIZE - 2; i++) {
            if (board[i][j] != EMPTY &&
                board[i][j] == board[i + 1][j] &&
                board[i][j] == board[i + 2][j]) {

                // Add points to current player
                if (currentPlayer == 1)
                    player1Score += 3;
                else
                    player2Score += 3;

                // Remove matched gems
                board[i][j] = EMPTY;
                board[i + 1][j] = EMPTY;
                board[i + 2][j] = EMPTY;
            }
        }
    }
}

void Game::fillBoard() {
    // Move gems down to fill empty spaces
    for (int j = 0; j < BOARD_SIZE; j++) {
        int emptySpaces = 0;
        for (int i = BOARD_SIZE - 1; i >= 0; i--) {
            if (board[i][j] == EMPTY) {
                emptySpaces++;
            }
            else if (emptySpaces > 0) {
                // Move gem down
                board[i + emptySpaces][j] = board[i][j];
                board[i][j] = EMPTY;
            }
        }

        // Fill top rows with new gems
        for (int i = 0; i < emptySpaces; i++) {
            board[i][j] = static_cast<Gem>(gemDist(rng));
        }
    }
}

bool Game::hasPossibleMoves() {
    // Check if there are any valid moves left
    // This is a simplified implementation

    // Check horizontal swaps
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - 1; j++) {
            // Try swap
            std::swap(board[i][j], board[i][j + 1]);

            // Check if this creates a match
            bool hasMatch = checkForMatches();

            // Swap back
            std::swap(board[i][j], board[i][j + 1]);

            if (hasMatch) {
                return true;
            }
        }
    }

    // Check vertical swaps
    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i < BOARD_SIZE - 1; i++) {
            // Try swap
            std::swap(board[i][j], board[i + 1][j]);

            // Check if this creates a match
            bool hasMatch = checkForMatches();

            // Swap back
            std::swap(board[i][j], board[i + 1][j]);

            if (hasMatch) {
                return true;
            }
        }
    }

    return false;
}

Status Game::status() const {
    // If game is still active, return ONGOING
    if (gameActive && movesRemaining > 0) {
        return ONGOING;
    }

    // Otherwise, determine winner based on scores
    if (player1Score > player2Score) {
        return PLAYER_1_WINS;
    }
    else if (player2Score > player1Score) {
        return PLAYER_2_WINS;
    }
    else {
        return DRAW;
    }
}

void Game::display() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    // Display the board
    os << "  ";
    for (int j = 0; j < game.BOARD_SIZE; j++) {
        os << j << " ";
    }
    os << "\n";

    for (int i = 0; i < game.BOARD_SIZE; i++) {
        os << i << " ";
        for (int j = 0; j < game.BOARD_SIZE; j++) {
            // Display gem with a character
            char gemChar;
            switch (game.board[i][j]) {
            case DIAMOND: gemChar = 'D'; break;
            case RUBY: gemChar = 'R'; break;
            case EMERALD: gemChar = 'E'; break;
            case SAPPHIRE: gemChar = 'S'; break;
            case AMETHYST: gemChar = 'A'; break;
            case TOPAZ: gemChar = 'T'; break;
            default: gemChar = '.'; break;
            }
            os << gemChar << " ";
        }
        os << "\n";
    }

    // Display game info
    os << "Player 1 Score: " << game.player1Score << "\n";
    os << "Player 2 Score: " << game.player2Score << "\n";
    os << "Current Player: " << game.currentPlayer << "\n";
    os << "Moves Remaining: " << game.movesRemaining << "\n";

    return os;
}

// Main function
int main() {
    // Create a new game
    Game game;

    // Main game loop
    while (game.status() == ONGOING) {
        // Display current state
        game.display();

        // Get input
        int row1, col1, row2, col2;
        std::cout << "Player " << game.getCurrentPlayer() << "'s turn.\n";
        std::cout << "Enter row and column of first gem: ";
        std::cin >> row1 >> col1;
        std::cout << "Enter row and column of second gem: ";
        std::cin >> row2 >> col2;

        // Make move
        if (!game.play(row1, col1, row2, col2)) {
            std::cout << "Invalid move. Try again.\n";
        }
    }

    // Display final state
    game.display();

    // Display results
    switch (game.status()) {
    case PLAYER_1_WINS:
        std::cout << "Player 1 wins!\n";
        break;
    case PLAYER_2_WINS:
        std::cout << "Player 2 wins!\n";
        break;
    case DRAW:
        std::cout << "It's a draw!\n";
        break;
    default:
        break;
    }

    return 0;
}

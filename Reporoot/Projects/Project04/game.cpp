#include "Game.h"
#include <iostream>

Game::Game() : gameState(GameState::Running) {
    randomizeBoard();
    while (!hasPossibleMoves()) {  // Ensure starting board has possible moves
        randomizeBoard();
    }
}

GemType Game::getRandomGem() const {
    static std::default_random_engine engine{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(0, static_cast<int>(GemType::COUNT) - 1);
    return static_cast<GemType>(dist(engine));
}

void Game::randomizeBoard() {
    for (auto& row : board)
        for (auto& gem : row)
            gem = getRandomGem();
}

void Game::play() {
    if (gameState != GameState::Running) return;

    if (hasMatch()) {
        removeMatches();
        dropGems();
    }
    else if (!hasPossibleMoves()) {
        gameState = GameState::Lost;
    }
}

GameState Game::status() const {
    return gameState;
}

void Game::swap(int row1, int col1, int row2, int col2) {
    if (!isAdjacent(row1, col1, row2, col2)) return;

    std::swap(board[row1][col1], board[row2][col2]);

    if (!hasMatch()) {  // Undo swap if no match created
        std::swap(board[row1][col1], board[row2][col2]);
    }
}

bool Game::isAdjacent(int row1, int col1, int row2, int col2) const {
    int dr = abs(row1 - row2);
    int dc = abs(col1 - col2);
    return (dr + dc == 1);
}

bool Game::hasMatch() const {
    // Check horizontal and vertical matches
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (checkMatchAt(row, col))
                return true;
        }
    }
    return false;
}

bool Game::checkMatchAt(int row, int col) const {
    GemType gem = board[row][col];
    if (gem == GemType::COUNT) return false; // invalid gem

    // Check horizontal
    if (col <= COLS - 3) {
        if (board[row][col + 1] == gem && board[row][col + 2] == gem)
            return true;
    }

    // Check vertical
    if (row <= ROWS - 3) {
        if (board[row + 1][col] == gem && board[row + 2][col] == gem)
            return true;
    }

    return false;
}

void Game::removeMatches() {
    // Mark gems to remove (true = remove)
    std::array<std::array<bool, COLS>, ROWS> toRemove{};
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            GemType gem = board[row][col];
            if (gem == GemType::COUNT) continue;

            // Check horizontal match of 3+
            if (col <= COLS - 3) {
                if (board[row][col + 1] == gem && board[row][col + 2] == gem) {
                    toRemove[row][col] = true;
                    toRemove[row][col + 1] = true;
                    toRemove[row][col + 2] = true;
                    int k = col + 3;
                    while (k < COLS && board[row][k] == gem) {
                        toRemove[row][k] = true;
                        k++;
                    }
                }
            }

            // Check vertical match of 3+
            if (row <= ROWS - 3) {
                if (board[row + 1][col] == gem && board[row + 2][col] == gem) {
                    toRemove[row][col] = true;
                    toRemove[row + 1][col] = true;
                    toRemove[row + 2][col] = true;
                    int k = row + 3;
                    while (k < ROWS && board[k][col] == gem) {
                        toRemove[k][col] = true;
                        k++;
                    }
                }
            }
        }
    }

    // Replace removed gems with empty placeholder (GemType::COUNT)
    for (int row = 0; row < ROWS; ++row)
        for (int col = 0; col < COLS; ++col)
            if (toRemove[row][col])
                board[row][col] = GemType::COUNT;
}

void Game::dropGems() {
    // Gravity: drop gems down to fill empty spots (GemType::COUNT)
    for (int col = 0; col < COLS; ++col) {
        int emptyRow = ROWS - 1;
        for (int row = ROWS - 1; row >= 0; --row) {
            if (board[row][col] != GemType::COUNT) {
                board[emptyRow][col] = board[row][col];
                if (emptyRow != row)
                    board[row][col] = GemType::COUNT;
                emptyRow--;
            }
        }
        // Fill remaining empty cells at top with new random gems
        for (int r = emptyRow; r >= 0; --r) {
            board[r][col] = getRandomGem();
        }
    }
}

bool Game::hasPossibleMoves() const {
    // Check if any swap results in a match
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (col < COLS - 1) {
                // Swap right and check
                std::swap(board[row][col], board[row][col + 1]);
                if (hasMatch()) {
                    std::swap(board[row][col], board[row][col + 1]);
                    return true;
                }
                std::swap(board[row][col], board[row][col + 1]);
            }
            if (row < ROWS - 1) {
                // Swap down and check
                std::swap(board[row][col], board[row + 1][col]);
                if (hasMatch()) {
                    std::swap(board[row][col], board[row + 1][col]);
                    return true;
                }
                std::swap(board[row][col], board[row + 1][col]);
            }
        }
    }
    return false;
}

void Game::draw(SDL_Renderer* renderer) const {
    const int size = 50;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            SDL_Rect rect = { col * size, row * size, size, size };
            switch (board[row][col]) {
            case GemType::Red:    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
            case GemType::Green:  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break;
            case GemType::Blue:   SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); break;
            case GemType::Yellow: SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break;
            case GemType::Purple: SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255); break;
            case GemType::Orange: SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break;
            default:              SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); break; // empty / removed
            }
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
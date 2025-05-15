#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <array>
#include <random>

enum class GameState {
    Running,
    Won,
    Lost,
    Draw
};

enum class GemType {
    Red,
    Green,
    Blue,
    Yellow,
    Purple,
    Orange,
    COUNT
};

class Game {
public:
    Game();

    void play();
    GameState status() const;
    void draw(SDL_Renderer* renderer) const;
    void swap(int row1, int col1, int row2, int col2);
    bool isAdjacent(int row1, int col1, int row2, int col2) const;

private:
    static const int ROWS = 8;
    static const int COLS = 8;

    std::array<std::array<GemType, COLS>, ROWS> board;
    GameState gameState;

    void randomizeBoard();
    bool hasMatch() const;
    void removeMatches();
    void dropGems();
    GemType getRandomGem() const;
    bool hasPossibleMoves() const;
    bool checkMatchAt(int row, int col) const;
};

#endif
#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
#include <vector>
#include <ncurses.h>


class Game {
  private:
    std::vector<std::vector<int>> grid;
    int gen_num = 0;

    bool isGameRunning = true;
    bool isCellChanged = false;
    bool isGenDead = true;

    int countNeighboursNum(int row, int col);

  public:
    void initGrid();
    void gameLoop();
    void printGen();

};
#endif

#include "../include/Game.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <string>

void Game::initGrid() {

    std::vector<std::vector<int>> grid_template = 
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::swap(grid, grid_template);
}

int Game::countNeighboursNum(int row, int col) {
  int neighbours_num = 0;
  int grid_size = grid.size();

  if (row+1 < grid_size && col+1 < grid_size && row-1 >= 0 && col-1 >= 0)
    neighbours_num = grid[row+1][col] + grid[row-1][col] + grid[row][col+1] + grid[row][col-1] + grid[row+1][col+1] + grid[row-1][col-1] + grid[row+1][col-1] + grid[row-1][col+1];

  return neighbours_num;
}

void Game::gameLoop() {
  int scr_row, scr_col;

  setlocale(LC_ALL, "");
  initscr();
  getmaxyx(stdscr, scr_row, scr_col);

  while(isGameRunning) {
    std::vector<std::vector<int>> grid_copy = grid;
    isCellChanged = false;
    isGenDead = true;

    gen_num++;
    
    clear();
    move(scr_row / 4, scr_col);
    printGen();
    refresh();
    //std::cout << std::endl;
    for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[0].size(); col++) {
        int neighbours_num = countNeighboursNum(row, col);
        //std::cout << neighbours_num << " ";

        if (grid[row][col])
          isGenDead = false;
        if (grid[row][col] && neighbours_num != 2 && neighbours_num != 3) {
          isCellChanged = true;
          grid_copy[row][col] = 0;
        }
        else if (!grid[row][col] && neighbours_num == 3) {
          isCellChanged = true;
          grid_copy[row][col] = 1;
        }
      }
      //std::cout << std::endl;
    }

    grid = grid_copy;

    if (isGenDead || !isCellChanged)
      isGameRunning = false;
    sleep(1);
  }
  endwin();
}

void Game::printGen() {
  //system("clear");
  //std::cout << "Gen " << gen_num << std::endl;
  printw("Gen %d\n", gen_num);
    for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[0].size(); col++) {
        if (grid[row][col] == 1)
          //std::cout << "■ ";
          printw("■ ");
        else
          //std::cout << "☐ ";
          printw("☐ ");
      }
      //std::cout << std::endl;
      printw("\n");
    }
}


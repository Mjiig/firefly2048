#include <iostream>
#include <iomanip>
#include "randint.h"
#include "board.h"

const int Board::values[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

//This appears to work, which is a minor miracle. Plz refactor
//Here be dragons
bool Board::move(int startx, int endx, int starty, int endy, int dx, int dy, int sx, int sy){
  bool merged[4][4];
  for(int x=0; x<4; x++){
    for(int y=0; y<4; y++){
      merged[x][y]=false;
    }
  }

  bool moved=false;

  for(int x=startx + dx; x!=endx; x+=dx){
    for(int y=starty + dy; y!=endy; y+=dy){
      if(grid[x][y]==0){
        continue;
      }

      int tx=x, ty=y;
      while(tx+sx != startx && ty+sy != starty && grid[tx+sx][ty+sy] == 0){
        tx+=sx;
        ty+=sy;
        moved=true;
      }

      if(tx+sx != startx && ty+sy != starty && grid[x][y]==grid[tx+sx][ty+sy] && !merged[tx+sx][ty+sy]){
        grid[tx+sx][ty+sy]++;
        merged[tx+sx][ty+sy]=true;
        grid[x][y]=0;
        score+=values[grid[tx+sx][ty+sy]];
        moved=true;
      }else{
        int temp = grid[x][y]; //Save value in case we haven't moved
        grid[x][y]=0;
        grid[tx][ty]=temp;
      }
    }
  }

  if(moved){
    add_piece();
  }

  return moved;
}

bool Board::moveleft(){
  return move(-1, 4, -1, 4, 1, 1, -1, 0);
}

bool Board::moveright(){
  return move(4, -1, -1, 4, -1, 1, 1, 0);
}

bool Board::moveup(){
  return move(-1, 4, -1, 4, 1, 1, 0, -1);
}

bool Board::movedown(){
  return move(-1, 4, 4, -1, 1, -1, 0, 1);
}

void Board::add_piece(){
  int zeroes=0;
  for(int x = 0; x<4; x++){
    for(int y = 0; y<4; y++){
      if(grid[x][y]==0) zeroes++;
    }
  }

  int i = r.getInt(zeroes);

  for(int x = 0; x<4; x++){
    for(int y=0; y<4; y++){
      if(grid[x][y]==0){
        if(i==0){
          grid[x][y]=get_new_piece();
        }
        i--;
      }
    }
  }
}

int Board::get_new_piece(){
  if(r.getInt(4)==0){
    return 2; // 4 tile
  }
  return 1; // 2 tile
}

Board::Board(){
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      grid[i][j]=0;
    }
  }
  score=0;
}

void Board::pretty_print(){
  std::cout << "---------------------" << std::endl;
  for(int y=0; y<4; y++){
    for(int x=0; x<4; x++){
      std::cout << "|" << std::setw(4);
      if(grid[x][y]){
        std::cout <<  values[grid[x][y]];
      }else{
        std::cout << "";
      }
    }
    std::cout << "|" << std::endl << "---------------------"<< std::endl;
  }
}

int Board::getscore(){
  return score;
}

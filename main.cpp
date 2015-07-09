#include <iostream> 
#include "board.h"

int main(){
  Board b;
  char in;
  bool running=true;

  b.add_piece();
  b.add_piece();

  b.pretty_print();

  while(running){
    bool moved=false;
    std::cin >> in;
    switch(in){
    case 'w':
      std::cout << b.moveup() << std::endl;
      moved=true;
      break;
    case 'a':
      std::cout << b.moveleft() << std::endl;
      moved=true;
      break;
    case 's':
      std::cout << b.movedown() << std::endl;
      moved=true;
      break;
    case 'd':
      std::cout << b.moveright() << std::endl;
      moved=true;
      break;
    case 'q':
      running=false;
      break;
    }

    if(moved){
      b.pretty_print();
    }
  }

  return 0;
}

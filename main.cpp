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
      b.moveup();
      moved=true;
      break;
    case 'a':
      b.moveleft();
      moved=true;
      break;
    case 's':
      b.movedown();
      moved=true;
      break;
    case 'd':
      b.moveright();
      moved=true;
      break;
    case 'q':
      running=false;
      break;
    }

    if(moved){
      b.pretty_print();
      std::cout << b.getscore() << std::endl;
    }

    Board copy = b;
    if(!copy.moveright() && !copy.moveleft() && !copy.moveup() && !copy.movedown()){ //This can definitely be done more efficiently
      running = false;
    }
  }

  std::cout << "You scored " << b.getscore() << " points" << std::endl; 

  return 0;
}

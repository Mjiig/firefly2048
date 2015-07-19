#include <iostream> 
#include "board.h"
#include "network.h"
#include "rand.h"

int human_2048(){
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

    running = b.moveable();
  }

  std::cout << "You scored " << b.getscore() << " points" << std::endl; 

  return 0;
}

int main(){
  std::vector<double> weights;
  Rand r;

  for(int i=0; i<4160; i++){
    weights.push_back(r.getDouble(0.0, 1.0));
  }

  Network n(weights);

  for(int j=0; j<1000; j++){

    Board b;
    bool movemade=true;
    std::vector<double> ins;
    std::vector<double> outs;
    int max=0;

    while(b.moveable()){
      if(movemade){
        ins = b.getGrid();
        outs=n.output(ins);
      }else{
        outs[max]= -1; //Must be minimum value
      }

      for(int i=0; i<4; i++){
        if(outs[i]>outs[max]){
            max=i;
        }
      }

      movemade=false;
      switch(max){
      case 0:
        movemade=b.moveup();
        break;
      case 1:
        movemade=b.moveright();
        break;
      case 2:
        movemade=b.movedown();
        break;
      case 3:
        movemade=b.moveleft();
        break;
      }
    }

    std::cout << b.getscore() << std::endl;
  }

  return 0;
}

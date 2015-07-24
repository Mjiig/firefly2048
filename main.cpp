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

int evaluateNetwork(std::vector<double> weights){
  Network n(weights);
  int total = 0;

  for(int j=0; j<50; j++){

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

    total += b.getscore();
  }
  return total/50;
}

std::vector<std::vector<double>> initialNetworks(){
  Rand r;
  std::vector<std::vector<double>> ret;

  for(int i = 0; i<100; i++){
    std::vector<double> current;
    for(int j=0; j<4160; j++){
      current.push_back(r.getDouble(0.0, 1.0));
    }
    ret.push_back(current);
  }
  return ret;
}

std::vector<int> evaluateSwarm(std::vector<std::vector<double>> networks){
  std::vector<int> ret;
  for(auto w: networks){
    ret.push_back(evaluateNetwork(w));
  }
  return ret;
}

double getDistance(std::vector<double> a, std::vector<double> b){
  double total=0.0;
  for(size_t i=0; i<a.size(); i++){
    total+=(a[i]-b[i])*(a[i]-b[i]);
  }
  return std::sqrt(total);
}


std::vector<std::vector<double>> updateSwarm(std::vector<std::vector<double>> swarm, std::vector<int> scores, double randScale){
  std::vector<std::vector<double>> ret = swarm;

  for(size_t i=0; i<swarm.size(); i++){
    for(size_t j=0; j<swarm.size(); j++){
      if(scores[i]<scores[j]){
        continue;
      }

      double distance = getDistance(swarm[i], swarm[j]);
      for(size_t k=0; k<swarm[i].size(); k++){
        ret[i][k]+=(swarm[j][k]-swarm[i][k])*std::exp(-5*distance);
      }

    }

    Rand r;
    std::vector<double> random=r.getUniformVector(swarm[i].size());
    for(size_t j=0; j<swarm[i].size(); j++){
      ret[i][j]+=random[j]*randScale;
    }
  }
  return ret;
}

double average(std::vector<int> scores){
  double total = 0.0;
  for(int x: scores){
    total+=x;
  }
  return total/scores.size();
}

int max(std::vector<int> scores){
  int best = 0;
  for(int x: scores){
    if(x>best){
      best=x;
    }
  }
  return best;
}


int main(){
  std::vector<std::vector<double>> weights = initialNetworks();
  std::vector<int> scores;
  for(double scale=1.0; scale>0.0001; scale*=0.999){
    scores=evaluateSwarm(weights);
    std::cout << max(scores) << "     " << average(scores) << "      " << scale << std::endl;
    weights = updateSwarm(weights, scores, scale);
  }

  return 0;
}

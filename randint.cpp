#include "randint.h"

RandInt::RandInt() : e(std::random_device()()){
}

int RandInt::getInt(int n){
  std::uniform_int_distribution<> dist(0, n-1);
  return dist(e);
}

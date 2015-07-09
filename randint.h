#include <random>

#ifndef RANDINT_H
#define RANDINT_H

class RandInt{
  std::default_random_engine e;

 public:
  RandInt();
  int getInt(int n);
};

#endif

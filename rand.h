#include <random>

#ifndef RAND_H
#define RAND_H

class Rand{
  std::default_random_engine e;

 public:
  Rand();
  int getInt(int n);
  double getDouble(double mean, double stddev);
  std::vector<double> getUniformVector(int len);
};

#endif

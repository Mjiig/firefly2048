#include "rand.h"

Rand::Rand() : e(std::random_device()()){
}

int Rand::getInt(int n){
  std::uniform_int_distribution<> dist(0, n-1);
  return dist(e);
}

double Rand::getDouble(double mean, double stddev){
  std::normal_distribution<> dist(mean, stddev);
  return dist(e);
}

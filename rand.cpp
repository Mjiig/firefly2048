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

std::vector<double> Rand::getUniformVector(int len){
  std::vector<double> ret;
  double length=0.0;
  for(int i=0; i<len; i++){
    double x = getDouble(0.0, 1.0);
    ret.push_back(x);
    length+=x*x;
  }
  length=std::sqrt(length);
  for(int i=0; i<len; i++){
    ret[i]=ret[i]/length;
  }
  return ret;
}

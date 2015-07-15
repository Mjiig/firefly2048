#include <vector>
#include <memory>
#include "neuron.h"

#ifndef NETWORK_H
#define NETWORK_H

using std::vector;
using std::shared_ptr;
using std::unique_ptr;

class Network{
  shared_ptr<vector<unique_ptr<Neuron>>> inputs; //Probably need to implement some sort of special input Neuron for which we can override output
  shared_ptr<vector<unique_ptr<Neuron>>> outputs;

  vector<shared_ptr<vector<unique_ptr<Neuron>>>> neurons;

  vector<double> getCurrentWeights(int &start, int n, vector<double> weights);

 public:
  Network(std::vector<double> weights);
  double output();
};

#endif

#include <vector>
#include <cmath>
#include <memory>
#include "neuron.h"

Neuron::Neuron(std::vector<std::shared_ptr<Neuron>> in, std::vector<double> w){
  inputs = in;
  weights = w;
  calculated=false;
}

double sigmoid(double x){
  return 1.0/(1+std::exp(x));
}

double Neuron::output(){
  if(calculated){
    return result;
  }

  double total=0.0;

  for(size_t i=0; i<inputs.size(); i++){
    total+=inputs[i]->output() * weights[i];
  }

  result = sigmoid(total);
  calculated = true;
  return result;
}

void Neuron::reset(){
  calculated=false;
  for(std::shared_ptr<Neuron> n: inputs){
    n->reset();
  }
}

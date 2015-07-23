#include <vector>
#include <cmath>
#include <memory>
#include "neuron.h"

using std::shared_ptr;
using std::unique_ptr;
using std::vector;

ComputedNeuron::ComputedNeuron(shared_ptr<vector<unique_ptr<Neuron>>> in, vector<double> w){
  inputs = in;
  weights = w;
  calculated=false;
}

double sigmoid(double x){
  return 1.0/(1+std::exp(-x));
}

double ComputedNeuron::output(){
  if(calculated){
    return result;
  }

  double total=0.0;

  for(size_t i=0; i<(inputs->size()); i++){
    total+=(*inputs)[i]->output() * weights[i];
  }

  result = sigmoid(total);
  calculated = true;
  return result;
}

void ComputedNeuron::reset(){
  if(calculated){
    calculated=false;
    for(size_t i=0; i<inputs->size(); i++){
      inputs->at(i)->reset();
    }
  }
}
InputNeuron::InputNeuron(){
  value = 0.0;
}

void InputNeuron::setvalue(double v){
  value = v;
}

double InputNeuron::output(){
  return value;
}

void InputNeuron::reset(){}

#include <vector>
#include <memory>
#include "network.h"
#include "neuron.h"

/* A network is a 16 row neural network, where each row has 16 neurons
   The network weights are provided as a vector
   There are 16 input nodes and 4 output nodes
*/

using std::vector;
using std::shared_ptr;
using std::unique_ptr;

Network::Network(std::vector<double> weights){

  inputs.reset(new vector<unique_ptr<Neuron>>);
  unique_ptr<Neuron> s;
  for(int i=0; i<16; i++){
    s.reset(new InputNeuron());
    inputs->push_back(std::move(s)); //Use std::move to fix this!
  }

  shared_ptr<vector<unique_ptr<Neuron>>> previous = inputs;
  shared_ptr<vector<unique_ptr<Neuron>>> layer;

  int counter=0;

  for(int i=0; i<16; i++){
    layer.reset(new vector<unique_ptr<Neuron>>);

    for(int j=0; j<16; j++){

      //Pull 16 values out of weights vector
      vector<double> currentWeights = getCurrentWeights(counter, 16, weights);

      unique_ptr<Neuron> n;
      n.reset(new ComputedNeuron(previous, currentWeights)); 
      layer->push_back(std::move(n));
    }

    neurons.push_back(layer);
    previous=layer;
  }

  outputs.reset(new vector<unique_ptr<Neuron>>);
  for(int i=0; i<4; i++){
    vector<double> currentWeights = getCurrentWeights(counter, 16, weights);
    unique_ptr<Neuron> n;
    n.reset(new ComputedNeuron(previous, currentWeights));
    outputs->push_back(std::move(n));
  }
}

vector<double> Network::getCurrentWeights(int &start, int n, vector<double> weights){
  vector<double> ret;
  for(int i=start; i<start+n; i++){
    ret.push_back(weights.at(i));
  }
  start+=n;
  return ret;
}

vector<double> Network::output(vector<double> invalues)
{
  for(int i=0; i<16; i++){
    ((InputNeuron *)(inputs->at(i).get()))->setvalue(invalues.at(i));
  }

  vector<double> ret;
  for(int i=0; i<4; i++){
    ret.push_back(outputs->at(i)->output());
  }

  return ret;

}

#include <vector>
#include <memory>

#ifndef NEURON_H
#define NEURON_H

using std::shared_ptr;
using std::unique_ptr;
using std::vector;

class Neuron{
 public:
  virtual double output()=0;
  virtual void reset()=0;
  virtual ~Neuron(){}; //Can't define the destructor as abstract since it needs behaviour. Doesn't matter than rule of 5 is broken since this class cannot be constructed
};

class ComputedNeuron: public Neuron{
 private:
  shared_ptr<vector<unique_ptr<Neuron>>> inputs;
  vector<double> weights;
  double result;
  bool calculated;

 public:
  ComputedNeuron(shared_ptr<vector<unique_ptr<Neuron>>> in, vector<double> w);
  double output();
  void reset();
};

class InputNeuron: public Neuron{
 private:
  double value;

 public:
  void setvalue(double v);
  InputNeuron(); 
  double output(); 
  void reset();
};

#endif

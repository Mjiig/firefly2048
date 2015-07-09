#include <vector>
#include <memory>

#ifndef NEURON_H
#define NEURON_H

class Neuron{
 private:
  std::vector<std::shared_ptr<Neuron>> inputs;
  std::vector<double> weights;
  double result;
  bool calculated;

 public:
  Neuron(std::vector<std::shared_ptr<Neuron>> in, std::vector<double> w);
  double output();
  void reset();
};


#endif

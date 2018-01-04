// Associative Probabalistic Filter - Zach Champion, Jan 1 2018

#ifndef AP_FILTER_H_
#define AP_FILTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

#define AP_FILTER_MAX_IN 12

class ApFilterInput {

public:

  // reliability
  float getReliability(float input_);

  // default constructor
  ApFilterInput();

  // initializer
  void init(int count_, float reliability_[]);

private:

  // reliability
  int reliability_count;
  float reliabilty[AP_FILTER_MAX_IN];

};

class ApFilter {

public:

  // tuning parameters
  float apathy; // the higher this is, the less each input cares about each other

  // inputs
  int getInputCount(); // getter for input_count
  void setInputs(int count_, ApFilterInput inputs_[]); // updates input_count and inputs[]

  // default constructor
  ApFilter();

  // initializer
  void init(float apathy_, int count_, ApFilterInput inputs_[]);

  // run the filter
  float run(float inputs_[]);

private:

  // inputs
  int input_count; // amount of inputs used by the filter
  ApFilterInput inputs[]; // array of input objects

};

#ifdef __cplusplus
}
#endif

#endif

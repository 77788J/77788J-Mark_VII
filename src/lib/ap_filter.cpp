#include "ap_filter.h"
#include "math.h"


ApFilter :: ApFilter() {}

void ApFilter :: init(float apathy_, int count_,  ApFilterInput inputs_[AP_FILTER_MAX_IN]) {

  setInputs(count_, inputs_);
  apathy = apathy_;

}

float ApFilter :: run(float inputs_[AP_FILTER_MAX_IN]) {

  // create assiciations 2D array to store the differences between all inputs
  float associations[input_count][input_count];

  // fill associations array with the errors between each pair of inputs
  for (int i = 0; i < input_count; i++) {
    for (int j = 0; j < input_count; j++) {

      if (i == j) { // no reason to do all those calculations
        associations[i][j] = 1;
      }
      else {
        float error = abs(inputs_[i] - inputs_[j]); // calc error
        associations[i][j] = apathy / (error + apathy); // convert to percentage
      }
    }
  }

  // create array of confidence levels (one per input)
  float confidences[input_count];

  // loop through each input
  for (int i = 0; i < input_count; i++) {

    // declare 'c' (the confidence level of the current input)
    float c = 1;

    // loop through all other inputs and take into account their assiciated confidence percentage
    for (int j = 0; j < input_count; j++) {
      if (i != j) c *= 1 - associations[i][j];
    }

    // take into account each input's reliability
    c = 1 - (c * (1 - inputs[i].getReliability(inputs_[i])));

    // store 'c' in confidences array
    confidences[i] = c;
  }

  // scale all confidence levels to add to 1
  float total = 0;
  for (int i = 0; i < input_count; i++) {
    total += confidences[i];
  }
  if (total != 0) {
    for (int i = 0; i < input_count; i++) {
      confidences[i] /= total;
    }

    // apply weighted average to all inputs
    float result = 0;
    for (int i = 0; i < input_count; i++) {
      result += inputs_[i] * confidences[i];
    }

    // return the final result
    return result;
  }
  else return 0;
}

void ApFilter :: setInputs(int count_, ApFilterInput* inputs_) {

  // save new input count (and make sure it's at most AP_FILTER_MAX_IN)
  input_count = min(count_, AP_FILTER_MAX_IN);

  // store new inputs in internal array
  for (int i = 0; i < input_count; i++) {
    inputs[i] = inputs_[i];
  }
}

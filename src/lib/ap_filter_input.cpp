#include "ap_filter.h"
#include "math.h"

// this object is used as an input for the AP filter
// reliability is an array of size AP_FILTER_MAX_INPUT
// the array is used to determine the baseline reliability of a sensor
// reliability is a polynomial, with each element in the array being a coefficent
// for example, 2x^2 + 5x - 1 would be {2, 5, -1}
// reliability_count stores how many elements should be used
// the array technically has AP_FILTER_MAX_INPUT entries, so it needs to know when to stop
// often, reliability_count will be 1 and the array will have only 1 element
// this would effectively produce a constant weight
// while the filter works with constant weights, the polynomial makes it MUCH beter, especially for gyros

ApFilterInput :: ApFilterInput() {}

void ApFilterInput :: init(int count_, float *reliability_) {
  reliability_count = count_;
  for (int i = 0; i < reliability_count; i++) {
    reliabilty[i] = reliability_[i];
  }
}

float ApFilterInput :: getReliability(float input_) {

  float r = 0;

  printf("r %d\n\n", reliability_count);

  for (int i = 0; i < reliability_count; i++) {
    r += reliabilty[i] * pow(input_, reliability_count - 1 - i);
    printf("RE: %d\n", i);
  }

  return r;
}

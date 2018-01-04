#include "ap_filter.h"
#include "math.h"

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

  reliability_count = 1;

  // for (int i = 0; i < reliability_count; i++) {
  //   // r += reliabilty[i] * pow(input_, reliability_count - 1 - i);
  //   printf("RE: %d\n", i);
  // }

  return r;
}

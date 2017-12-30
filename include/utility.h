#ifndef UTILITY_H_
#define UTILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <limits.h>

#define FLOAT_MAX 3.40282e+38

int sign(float x);
float limit(float val, float min, float max);
float wrap(float val, float min, float max);
float calcRpm(float error, int interval);

#ifdef __cplusplus
}
#endif

#endif

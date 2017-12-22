#ifndef UTILITY_H_
#define UTILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

float limit(float val, float min, float max);
float wrap(float val, float min, float max);

#ifdef __cplusplus
}
#endif

#endif

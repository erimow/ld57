#include "efuncs.h"
#include <math.h>
#include <stdio.h>

fvec2 vec2(float x, float y) { return (fvec2){x, y}; }
int divideUp(int numerator, int denominator) {
  return (numerator % denominator == 0) ? numerator / denominator
                                        : (numerator / denominator) + 1;
}

float maxf(float number, float maxValue) {
  return (number > maxValue) ? maxValue : number;
}

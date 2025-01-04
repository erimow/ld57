#ifndef efuncs
#define efuncs

typedef struct fvec2 {
  float x, y;
} fvec2;

fvec2 vec2(float x, float y);
extern int divideUp(int numerator,
                    int denominator); // Divides an int but rounds up.
extern float maxf(float number,
                  float maxValue); // If number exceeds max, then set to max.

#endif

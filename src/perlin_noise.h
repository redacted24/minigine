#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <vector>

/**
 * @class PerlinNoise
 * @brief Implementation of Perlin noise from Ken Perlin's implementation. See
 * https://cs.nyu.edu/~perlin/noise/
 *
 */
class PerlinNoise {
public:
  PerlinNoise();
  double noise(double x, double y, double z);
  double fade(double t);
  double lerp(double t, double a, double b);
  double grad(int hash, double x, double y, double z);
  std::vector<int> p;
  std::vector<int> permutation;
};

#endif // PERLIN_NOISE_H

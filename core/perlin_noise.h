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
  double noise(double p_x, double p_y, double p_z);
  double fade(double p_t);
  double lerp(double p_t, double p_a, double p_b);
  double grad(int p_hash, double p_x, double p_y, double p_z);
  std::vector<int> p;
  std::vector<int> permutation;
};

#endif // PERLIN_NOISE_H

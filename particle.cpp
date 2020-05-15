#include "particle.h"

Particle::Particle() : x(0), y(0), z(0), velo(0, 0, 0) {}
Particle::Particle(double x, double y, double z, Vec3f v) : x(x), y(y), z(z), velo(v) {}


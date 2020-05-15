// SAMPLE_SOLUTION
#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec.h"
#include "Mat.h"
#include <vector>


#include <FL/gl.h>
#include <stdlib.h>

class ParticleSlice {
public:
    Vec3f pos;
    double t;

    ParticleSlice() :pos(0, 0, 0), t(0) {}
    ParticleSlice(Vec3f temp, double t) :pos(temp), t(t) {}
};

class Particle {
private:

public:
    double x;
    double y;
    double z;
    Vec3f velo;
    //vector<ParticleSlice> ps;

    Particle();
    Particle(double x, double y, double z, Vec3f v);

};

#endif 
#pragma warning(disable : 4786)

#include "particleSystem.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <vector>
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <iostream>
using namespace std;


/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() :delta(0.1)
{
	// TODO

	bake_start_time = 0;
	bake_end_time = 30;
	bake_fps = 30;

	simulate = false;
}





/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem()
{
	// TODO
}


/******************
 * Simulation fxns
 ******************/

 /** Start the simulation */
void ParticleSystem::startSimulation(float t)
{

	// TODO

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	bake_end_time = -1;
	simulate = true;
	dirty = true;

	//computeForcesAndUpdateParticles(t);

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{

	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

	v.clear();
	ps.clear();

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{

	// TODO

	// These values are used by the UI
	simulate = false;
	dirty = true;

	stopSimulation(t);
	startSimulation(t);
}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	if (simulate == false) { return; }


	// TODO
	Vec3f accelerate(0, -5, -3);

	vector<Particle>::iterator it;
	for (it = v.begin(); it != v.end(); ++it) {
		//cout << "y " << it->y <<endl;
		//cout << "velo y " << it->velo[1] << endl;

		it->x += it->velo[0] * delta;
		it->y += it->velo[1] * delta;
		it->z += it->velo[2] * delta;

		//cout << "acc " << accelerate[1] << endl;
		//cout << "delta" << delta << endl;
		it->velo += accelerate * delta;

		//cout << "velo after y " << it->velo[1] << endl;
		Vec3f temp(it->x, it->y, it->z);
		//cout << "asd " << it->x << " " << it->y << " " << it->z << endl;
		bakeParticles(t, temp);
	}

	drawParticles(t);
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	if (simulate == false) { return; }
	//int a = 0;
	vector<ParticleSlice>::iterator i;
	for (i = ps.begin(); i != ps.end(); ++i) {
		if (i->t == t) {
			//a++;
			glPushMatrix();
			//cout << "a " << a << endl;
			//cout << "hh" << i->pos[0] << " " << i->pos[1] << " " << i->pos[2] << endl;
			glTranslated(i->pos[0], i->pos[1], i->pos[2]);
			glScaled(1, 1, 1);
			drawSphere(0.2);
			glPopMatrix();
		}
	}
}


/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t, Vec3f temp)
{
	bool exist = false;

	vector<ParticleSlice>::iterator i;
	for (i = ps.begin(); i != ps.end(); ++i) {
		if (i->t == t && i->pos == temp)
		{
			exist = true;
			break;
		}
	}

	if (exist == false) {
		ParticleSlice tempo(temp, t);
		ps.push_back(tempo);
	}

}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	ps.clear();
}

void ParticleSystem::addParticle(Particle a)
{
	v.push_back(a);
}
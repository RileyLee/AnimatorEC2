#pragma warning(disable : 4786)

#include "particleSystem.h"
#include "modelerui.h"


#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
//#include <limits>

using namespace std;

static float prevT = 0.0;

/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() {
	// Leave these here; the UI needs them to work correctly.
	dirty = false;
	simulate = false;
}




/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
}

extern float GLOBAL_restitution;

/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
  ParticleArr.clear();
  prevT = t;
	// YOUR CODE HERE

	// These values are used by the UI ...
	// negative bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	bake_end_time = -1;
	simulate = true;
	dirty = true;

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
  ParticleArr.clear();
	// YOUR CODE HERE

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
  ParticleArr.clear();
	// YOUR CODE HERE

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

Vec3f G = Vec3f(0, -9.12, 0);
Vec3f Drag = 1.2;

Vec3f P = Vec3f(0, 0.2, 0);
Vec3f N = Vec3f(0, 1, 0);

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t) {
  if(!simulate) {
	return;
  }
  
  float timeDiff = t - prevT;
  if(timeDiff < 0) {
	return;
  }
  std::vector<Particle>::iterator it = ParticleArr.begin();
  while(it != ParticleArr.end()) {
	if(t - it->creationTime > 2.5) {
	  it = ParticleArr.erase(it);
	  continue;
	}
	bool rev = (it->p - P) * N < 0 && it->v * N < 0;
	if(rev) {
	  Vec3f vn = (N * it->v) * N;
	  Vec3f vt = it->v - vn;
	  it->v = vt - GLOBAL_restitution * vn;
	}
	Vec3f newPos = it->p + timeDiff * it->v;
	Vec3f forceAccum(0.0, 0.0, 0.0);
	forceAccum += it->m * G;
	forceAccum += -Drag * it->v;
	it->v = it->v + timeDiff * forceAccum;
	it->p = newPos;
	it++;
  }
  prevT = t;
}


/** Render particles */
void ParticleSystem::drawParticles(float t) {
  if(!simulate) {
	return;
  }
  for (int i = 0; i < ParticleArr.size(); i++) {
	glPushMatrix();
	setDiffuseColor(0.8, 0.6, 0.0);
	setAmbientColor(0.8, 0.6, 0.0);
	glTranslatef(ParticleArr[i].p[0], ParticleArr[i].p[1], ParticleArr[i].p[2]);
	drawSphere(ParticleArr[i].radius);
	glPopMatrix();
  }
}



float rate = 100.0f;

extern Mat4f CameraTransforms;

extern Mat4f getModelViewMatrix();

void ParticleSystem::spawnParticles(float t) {
  float timeDiff = t - prevT;
  if(!simulate) {
	return;
  }
  if(timeDiff <= 0) {
	//std::cout << prevT << " " << t << " " << timeDiff << std::endl;
	return;
  }
  int numParticles = rate * timeDiff;
  Mat4f worldMatrix = CameraTransforms.inverse() * getModelViewMatrix();
  Particle p;
  p.creationTime = t;
  for(int i = 0; i < numParticles; i++) {
	bool leftRight = rand() % 2 == 0;
	bool topBottom = rand() % 2 == 0;
	float d = rand() / (float)RAND_MAX;
	float rad = d * 0.45;
	float bound = rad;
	d = rand() / (float)RAND_MAX;
	float rad_2 = pow(rad, 2);
	float x_2 = rad_2 * d;
	float y_2 = rad_2 - x_2;
	float x = sqrt(x_2);
	float y = sqrt(y_2);
	if(leftRight) {
	  x = -x;
	}
	if(topBottom) {
	  y = -y;
	}
	Vec4f localCoord = Vec4f(x, y, 0, 1);
	Vec4f fakeOrigin = (localCoord * 0.77);
	fakeOrigin[2] = 5;
	Vec4f diff = localCoord - fakeOrigin;
	Vec4f radius = worldMatrix  * localCoord;
	Vec3f v = worldMatrix * diff;
	v.normalize();
	v *= 1.5;
	//float y = radius[1];
	//Vec4f point(0.0, y, 0.0, 1);
	p.m = 0.05;
	p.p = radius;
	p.v = v;
	p.radius = 0.05;
	p.creationTime = ModelerUserInterface::getInstance()->getTime();
	ParticleArr.push_back(p);
  }
}



/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{
	// TODO (baking is extra credit)
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	// TODO (baking is extra credit)
}

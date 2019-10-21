#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "core.h"
#include <cmath>

/**
 * class World will be used to contain the objects being drawn
 */
class Particle {
public:
    //static int counter;
    static long counter;
	//assign an id to every particle
    long id;

    //the position of the particle in 3d space
    Vector3 position;

    //the current velocity of the particle
    Vector3 velocity;

    //the acceleration of the particle
    Vector3 acceleration;

    //the damping factor to simlate real life movement
    real damping;

    //the inverse of mass is stored because it is more efficient for calc
    real inverseMass;

    //the netforce
    Vector3 forceAccum;


    //Particle constructor
    Particle(Vector3 position, Vector3 velocity, Vector3 acceleration, real damping, real Mass);

    //this is used to clear the force accum
    void clearAccumulator();

    //this is used to integrate in time based on duration
    void integrate(real duration);

    //add force
    void addForce(Vector3 v);

    //get velocity
    void getVelocity(Vector3 *v);

    //get velocity 2
    Vector3 getVelocity();

    //get position
    Vector3 getPosition();

    //get position 2
    void getPosition(Vector3 * v);

    //get acceleration
    Vector3 getAcceleration();

    //get position 2
    void getAcceleration(Vector3 * v);

    //get damping
    real getDamping();

    //check for finite mass
    bool hasFiniteMass();

    //get mass
    real getMass();

    //draw a particle
    void draw();
};

#endif 


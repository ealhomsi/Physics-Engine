#ifndef PFGEN_H_
#define PFGEN_H_

#include "core.h"
#include "Particle.h"
#include <vector>
using namespace std;


/**
* this is a force generator that could be asked to generate a force
* on one or more particles
*/
//asbstract
class ParticleForceGenerator {
    public:
    /**
     * overload this implementation for specific force
     */

    //long id
    long id;

    virtual void updateForce(Particle * particle, real duration) = 0;
};

//gravity
class ParticleGravity: public ParticleForceGenerator {
    //hold all acceleration due to gravity
    Vector3 gravity;

    public:
    ParticleGravity(const Vector3 & gravity);

    //applies the gravitational force to the particle in question
    virtual void updateForce(Particle* particle, real duration);
};

//drag
class ParticleDrag: public ParticleForceGenerator {
    //hold the two real values k1 and k2
    real k1;
    real k2;

    //functions
    ParticleDrag(real k1, real k2): k1(k1), k2(k2) {};

    virtual void updateForce(Particle* particle, real duration);
};


//spring
class ParticleSpring: public ParticleForceGenerator {
    //hold the spring constant
    real springConstant;

    //hold the other particle
    Particle * other;

    //spring length at rest
    real restLength;

    public:
    //build this object
    ParticleSpring(Particle* other, real springConstant, real restLength);
    //update the force
    virtual void updateForce(Particle * p, real duration);

};


//anchored spring
class ParticleAnchoredSpring: public ParticleForceGenerator {
    //hold the anchor
    Vector3 * anchor;
    real springConstant;
    real restLength;

    ParticleAnchoredSpring(Vector3 * anchor, real springConstant, real restLength);
    virtual void updateForce(Particle* p, real duration);
};

//elastic bungee generator
class ParticleBungee: public ParticleForceGenerator {
    //the other particle
    Particle * other;

    //the spring contant
    real springConstant;

    //the rest length
    real restLength;

    public:
    ParticleBungee(Particle * p, real springConstant, real restLength);
    virtual void updateForce(Particle* p, real duration);
};

//water like effect for buoyancy
class ParticleBuoyancy: public ParticleForceGenerator {
    // max depth
    real maxDepth;

    //the volume of the object
    real volume;

    //the height of the water
    real waterHeight;

    //density of liquid
    real liquidDensity;

    //functions
    ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity =1000.0f);
    virtual void updateForce(Particle* p, real duration);

};

//keep track of forces registered on a particle
class ParticleForceRegisteration {
    public:
        Particle * particle;
        ParticleForceGenerator* fg;

        ParticleForceRegisteration();
        ParticleForceRegisteration(Particle* particle, ParticleForceGenerator *fg);
};

typedef std::vector<ParticleForceRegisteration> Registry;

//the registry
class ParticleForceRegistry {
    protected:
        //hold it inside a vector
        Registry registeration;

    public:
        //add a force to a particle
        void add(Particle* particle, ParticleForceGenerator *fg);

        //remove a force from a particle
        bool remove(Particle* particle, ParticleForceGenerator *fg);

        //clear all forces in the registry
        void clear();

        //call all the force generators to update the forces
        //of their corresponding particles
        void updateForces(real duration);

};

#endif 

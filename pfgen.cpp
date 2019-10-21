/** 
* the source code for the force generator
 */
#include "pfgen.h"


//the only method for the ParticleForceRegisteration
ParticleForceRegisteration::ParticleForceRegisteration(Particle *p , ParticleForceGenerator* fg) {
    this->particle = p;
    this->fg = fg;
}

//update all the forces in the registry
void ParticleForceRegistry::updateForces(real duration) {
    Registry::iterator i;
    for(i = registeration.begin(); i != registeration.end(); i++) {
        i->fg->updateForce(i->particle, duration);
    }
}


//add a force to the registeration
void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator *fg) {
    ParticleForceRegisteration pr(particle, fg);
    registeration.push_back(pr);
}

//remove a force from the registeration
bool  ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator *fg) {
    Registry::iterator i = registeration.begin();
    for(; i!=registeration.end(); i++) {
        if( i->particle == particle && i->fg == fg) {
            registeration.erase(i);
            return true;
        }
    }

    return false;
}

//clear the vector   
void  ParticleForceRegistry::clear() {
    registeration.clear();
}


//gravity code
//updateForceGravity
void ParticleGravity::updateForce(Particle* p, real duration) {
    
    //check if the particle has finite mass
    if(! p->hasFiniteMass()) {
        return;
    }

    // apply the mass calculated force to the particle
    p->addForce(gravity * p->getMass());
}

//drag force
void ParticleDrag::updateForce(Particle* particle, real duration) {
    Vector3 force;

    particle->getVelocity(&force);

    //calculate the total drag coefficient
    real dragCof = force.magnitude();

    dragCof = k1 * dragCof  + k2 * dragCof *dragCof;

    //calculate the force
    force.normalize();
    force *= dragCof;
    particle->addForce(force);
}


//spring
void ParticleSpring::updateForce(Particle* p, real duration) {
    Vector3 force;

    p->getPosition(&force);
    force -= other->getPosition();


    //calculate the magnitude of the force
    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude - restLength);
    magnitude *= springConstant;

    //caclulate the force
    force.normalize();
    force *= -magnitude;
    p->addForce(force);
}

//anchored spring
void ParticleAnchoredSpring::updateForce(Particle* p, real duration) {
    Vector3 force;
    p->getPosition(&force);
    force -= *anchor;

    //calculate the magnitude of the force
    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude - restLength);
    magnitude *= springConstant;

    //caclulate the force
    force.normalize();
    force *= -magnitude;
    p->addForce(force);
}

//bungee spring
void ParticleBungee::updateForce(Particle* p, real duration) {
    Vector3 force; //the main difference is that a bungee does nothing if it is compressed
    p->getPosition(&force);
    force -= other->getPosition();

    real magnitude = force.magnitude();

    //does not push
    if(magnitude <= restLength)
        return;

    magnitude -= restLength;
    magnitude *= springConstant;

    //caclulate the force
    force.normalize();
    force *= magnitude;
    p->addForce(force);
}


//buoyancy
void ParticleBuoyancy::updateForce(Particle* p, real duration) {
    //check the depth
    real depth = p->getPosition().y;

    //check if we are out of water
    if(depth >= waterHeight +maxDepth) return;

    Vector3 force(0,0,0);
    //check if we are at the maximum height
    if(depth <= waterHeight - maxDepth) {
        force.y = liquidDensity * volume;
        p->addForce(force);
        return;
    }

    //other wise return partial force
    force.y = liquidDensity * volume *  (depth - maxDepth  - waterHeight) /(2 * maxDepth);
    p->addForce(force);
}


ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity): maxDepth(maxDepth), volume(volume), waterHeight(waterHeight), liquidDensity(liquidDensity) {}
ParticleBungee::ParticleBungee(Particle * p, real springConstant, real restLength) : restLength(restLength), springConstant(springConstant), other(p) {}
ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 * anchor, real springConstant, real restLength) : restLength(restLength), springConstant(springConstant), anchor(anchor) {}
ParticleSpring::ParticleSpring(Particle* other, real springConstant, real restLength) : other(other), restLength(restLength), springConstant(springConstant) {}

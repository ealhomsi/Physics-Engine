#ifndef WORLD_H_
#define WORLD_H_
#include <vector>
#include "Particle.h"

using namespace std;

/**
 * class World will be used to contain the objects being drawn
 */
class World {
public:
	vector<Particle*>  * objects;

    World();
    virtual ~World();

    //methods
    void add(Particle* o);
    bool remove(Particle* o);
    void draw();
};

#endif 

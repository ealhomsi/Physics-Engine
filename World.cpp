#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include "World.h"

/**
* draw each member of the world
*/
void World::draw() {
	for(vector<Particle*>::iterator i= objects->begin(); i!= objects->end(); i++) {
		(*i)->draw();
	}
}

/**
* add a physical object to the world
*/
void World::add(Particle* o) {
	objects->push_back(o);
}

/**
* remove a physical object from the world
*/
bool World::remove(Particle* o) {
	for(vector<Particle*>::iterator i= objects->begin(); i!= objects->end(); i++) {
		if(o->id == (*i)->id) {
			objects->erase(i);
			return true;
		}
	}
	return false;
}

/**
* init the world
*/
World::World() {
	objects = new vector<Particle*>();
}

/**
* destroy the world
*/
World::~World() {
	objects->clear();
}


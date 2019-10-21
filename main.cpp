
#include "Viewer.h"

/**
 * Main
 */
int  main(int ac, char *av[])
{
	//define world
	World* w = new World();


	//define particle 1
	Vector3 location(1.0f, 1.0f, 1.0f);
	Vector3 velocity(0,0,0);
	Vector3 acceleration(0,0,0);
	w->add(new Particle(location, velocity, acceleration, 0.0, 10));



    Viewer view(&ac, av, w);
    return 0;
}

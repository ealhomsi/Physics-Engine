#ifndef VIEWER_H_
#define VIEWER_H_

#include <GL/glut.h>
#include <GL/freeglut.h>
#include "World.h"

/**
 * Define Constants
 */
#define SCREEN_TITLE         "The Whole World"
#define SCREEN_WIDTH         600
#define SCREEN_HEIGHT         600
#define SCREEN_POSITION_X     100
#define SCREEN_POSITION_Y     100

/**
 * class Viewer will be used to view objects drawn
 */
class Viewer {
public:
    static World* wo;


    Viewer(int *ac, char *av[], World* w);
    virtual ~Viewer();

    static void setWorld(World * w);
    static void managerDisplay(void);
    static void managerKeyboard(unsigned char key, int x, int y);
    static void managerResize(int w, int h);
    static void managerMover(int w, int h);
    static void managerClicker(int button, int state, int x, int y);
};

#endif 

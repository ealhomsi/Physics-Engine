#include <iostream>
#include <math.h>
#include <iostream>
#include <string>

#include "Viewer.h"
#include "World.h"

World* Viewer::wo = NULL;

/**
 * Call iniProgram to have the t_badprog structure set.
 *
 * This method would draw the world and use it to update things up
 *
 */
void Viewer::managerDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel (GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
     //draw
    Viewer::wo->draw();
    glutSwapBuffers();
}

/**
 * By clicking ESC key, you close the window
 */
void Viewer::managerKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'a':
            glutPostRedisplay();
            cout<<"a was pressed";
            break;
    }

    //get rid of the x and y
    (void)(x);
    (void)(y);
}

/**
 * By resizing the window, the triangle stays with same proportions.
 */
void Viewer::managerResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

/**
 * Display in the console the x and y of the cursor when the mouse
 * is moved and a mouse button clicked.
 */
void Viewer::managerMover(int x, int y)
{
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl << std::endl;
}

/**
 * Display in the console the x and y of the cursor when a button
 * is clicked, showing its state (0 or 1) and which button is clicked.
 */
void Viewer::managerClicker(int button, int state, int x, int y)
{

    std::cout << "button = " << button << std::endl;
    std::cout << "state = " << state << std::endl;
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl << std::endl;
}

/**
 * All init methods needed by openGL.
 * In glutInitDisplayMode() we added GLUT_DOUBLE for double buffering.
 */
Viewer::Viewer(int *ac, char *av[], World* w) {
    setWorld(w);
    glutInit(ac,av);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(SCREEN_POSITION_X, SCREEN_POSITION_Y);

    glutCreateWindow(SCREEN_TITLE);

    glutDisplayFunc(&managerDisplay);
    glutKeyboardFunc(&managerKeyboard);
    glutReshapeFunc(&managerResize);
    glutMotionFunc(&managerMover);
    glutMouseFunc(&managerClicker);

    //init stuff goes here
    GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */

    /* Enable a single OpenGL light. */
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);


    /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);

    /* Setup the view of the cube. */
    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */ /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}

/**
set world
*/
void Viewer::setWorld(World* w) {
    Viewer::wo = w;
}


/**
 * Deleting
 */
Viewer::~Viewer() {
}


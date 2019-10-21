#include <assert.h>
#include "Particle.h"
#include <stdio.h>
#include "core.h"

long Particle::counter = 0;

Particle::Particle(Vector3 position, Vector3 velocity, Vector3 acceleration, real damping, real Mass){
    this->id = counter++;
    this->inverseMass = 1/Mass;
    this->damping = damping;
    this->acceleration = acceleration;
    this->position = position;
    this->velocity = velocity;
}

void Particle::integrate(real duration) {
    //check if the duartion is negative
    assert(duration > 0.0f);

    //update position
    position.addScaledVector(velocity, duration);

    //find acceleration
    Vector3 resultAcc = acceleration;
    resultAcc.addScaledVector(forceAccum, inverseMass);

    //update linear velocity
    velocity.addScaledVector(resultAcc, duration);

    //impose drag
    velocity *= real_pow(damping ,duration);

    //clear the force accum
    clearAccumulator();
}

//clear the force accum
void Particle::clearAccumulator() {
    forceAccum.clear();
}

//add force
void Particle::addForce(const Vector3 v) {
    forceAccum += v;
}

bool Particle::hasFiniteMass() {
    return (inverseMass != 0);
}

real Particle::getMass() {
    return 1.0/ inverseMass;
}


void Particle::getVelocity(Vector3 * v) {
    *v = velocity;
}

void Particle::getPosition(Vector3 * v) {
    *v = position;
}

void Particle::getAcceleration(Vector3 * v) {
    *v = acceleration;
}


Vector3 Particle::getVelocity() {
    return velocity;
}

Vector3 Particle::getPosition() {
    return position;
}

Vector3 Particle::getAcceleration() {
    return acceleration;
}

real Particle::getDamping() {
    return damping;
}

void Particle::draw() {
   static int k =0;
   k++;
  
    GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
    GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
    GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

    /* Setup cube vertex data. */
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  int i;
 

  

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(k-10, 0.0, -7.0 );
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-20, 0.0, 0.0, 1.0);


  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
  printf("drawn\n");
}

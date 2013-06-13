#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include "inc/GVector3.h"
#include "inc/GSphere.h"
#include "inc/GObject.h"
#define IMAGE_HEIGHT 500
#define IMAGE_WIDTH 500
#define SCENE_HEIGHT 40
#define SCENE_WIDTH 40
#define MAX_DISTANCE 1000000

GObject* test;
GVector3 CameraPosition(0.0f,0.0f,-10.0f);

void init() {
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  GVector3 center(0.0f,0.0f,0.0f);
  test=new GSphere(center,5.0f);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  glColor3f(1.0f,0.0f,0.0f);
  glBegin(GL_POINTS);
  for (int i=0;i<IMAGE_WIDTH;++i) {
    for (int j=0;j<IMAGE_HEIGHT;++j) {
      float x=-SCENE_WIDTH/2.0 + float(SCENE_WIDTH)/IMAGE_WIDTH*i;
      float y=-SCENE_HEIGHT/2.0 + float(SCENE_HEIGHT)/IMAGE_HEIGHT*j;
      GVector3 pixel(x,y,0);
      GVector3 direction=pixel-CameraPosition;
      Ray ray(CameraPosition,direction);
      float distance = MAX_DISTANCE;
      GVector3 Intersection;
      if (test->isIntersected(ray,distance)!=MISS) {
        glVertex3f(i,j,0);
      }
    }
  }
  glEnd();
  glutSwapBuffers();
}


void reshape(int w,int h) {
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,IMAGE_WIDTH,0,IMAGE_HEIGHT);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
  glutInitWindowSize (IMAGE_WIDTH, IMAGE_HEIGHT); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

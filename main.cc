#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include "inc/GVector3.h"
#include "inc/GFlat.h"
#include "inc/GSphere.h"
#include "inc/GObject.h"
#include "inc/LightSource.h"
#include "inc/DirectionalLight.h"
#include "inc/PointLight.h"
#define IMAGE_HEIGHT 800
#define IMAGE_WIDTH 600
#define SCENE_HEIGHT 80
#define SCENE_WIDTH 60
#define MAX_DISTANCE 1000000

std::vector<GObject*> object_list;
std::vector<LightSource*> light_list;
GVector3 CameraPosition(0.0f,0.0f,30.0f);

void init() {
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  glPointSize(5);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH,GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  
  glDepthFunc(GL_LEQUAL);
  GObject *test;
  test=new GSphere(GVector3(-5.0f,-5.0f,5.0f),5.0f);
  test->setKa(GVector3(0.2f,0.0f,0.0f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setShininess(30.0f);
  test->setReflectivity(0.5f);
  object_list.push_back(test);
  test=new GSphere(GVector3(5.0f,5.0f,-3.0f),3.0f);
  test->setShininess(80.0f);
  test->setKa(GVector3(0.0f,0.0f,0.3f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setReflectivity(0.5f);
  object_list.push_back(test);
  test=new GSphere(GVector3(-10.0f,10.0f,0.0f),4.0f);
  test->setShininess(30.0f);
  test->setKa(GVector3(0.0f,0.5f,0.0f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setReflectivity(0.8f);
  object_list.push_back(test);
  test=new GFlat(GVector3(0.0f,1.0f,0.0f),GVector3(0.0f,-10.0f,0.0f));
  test->setKa(GVector3(0.0f,0.5f,0.5f));
  test->setKd(GVector3(0.0f,0.2f,0.4f));
  test->setKs(GVector3(0.3f,0.0f,0.0f));
  test->setShininess(0.0f);
  test->setReflectivity(0.3f);
  object_list.push_back(test);
  PointLight* pl=new PointLight();
  pl->setPosition(GVector3(5.0f,15.0f,20.0f));
  pl->setKa(GVector3(1.0f,1.0f,1.0f));
  pl->setKd(GVector3(0.0f,0.0f,1.0f));
  pl->setKs(GVector3(1.0f,1.0f,1.0f));
  light_list.push_back(pl);
  pl=new PointLight();
  pl->setPosition(GVector3(0.0f,50.0f,-20.0f));
  pl->setKa(GVector3(1.0f,1.0f,1.0f));
  pl->setKd(GVector3(1.0f,0.0f,0.0f));
  pl->setKs(GVector3(0.0f,1.0f,0.0f));
  light_list.push_back(pl);
  //DirectionalLight* dl=new DirectionalLight();
  //dl->setDirection(GVector3(-1.0f,-5.0f,-4.0f));
  //dl->setKa(GVector3(0.3f,0.0f,0.0f));
  //dl->setKd(GVector3(1.0f,1.0f,1.0f));
  //dl->setKs(GVector3(1.0f,1.0f,1.0f));
  //light_list.push_back(dl);
}

GVector3 Tracer(const Ray& ray,int left,int last) {
  GVector3 color(0.0f,0.0f,0.0f);//background
  double distance = MAX_DISTANCE;
  double shade=1.0f;
  int IntersectionObject=-1;
  INTERSECTION_TYPE tmp;
  for (int k=0;k<object_list.size();++k) {
    GObject* obj=object_list.at(k);
    if (last==k)
      continue;
    if ((tmp=obj->isIntersected(ray,distance))!=MISS) {
      IntersectionObject=k;
    }
  }
  if (IntersectionObject==-1)
    return color;
  //now there is a intersection point
  GObject* obj=object_list.at(IntersectionObject);
  GVector3 point=ray.getPoint(distance);
  GVector3 tmpColor;
  for (int k=0;k<light_list.size();++k) {
    LightSource* ls = light_list.at(k);
    Ray testRay(point,ls->getLightDirection(point)*(-1.0f));
    for (int k=0;k<object_list.size();++k) {
      GObject* obj=object_list.at(k);
      if ((tmp=obj->isIntersected(testRay,distance))!=MISS) {
        if (k!=IntersectionObject)
          shade=0.0f;
        break;
      }
    }
    tmpColor = ls->calColor(obj,point,CameraPosition);
    tmpColor.normalize();
    tmpColor*=shade;
    color += tmpColor;
    color.normalize();
  }
  if (left==0)
    return color;
  GVector3 normal=obj->getNormal(point);
  normal.normalize();
  GVector3 rd=ray.getDirection()*(-1.0f);
  GVector3 reflectRayDirection=normal*(rd*normal)*2.0f-rd;
  Ray reflectRay(point,reflectRayDirection);
  GVector3 reflectColor=Tracer(reflectRay,left-1,IntersectionObject);
  color.normalize();
  //color+=GVector3(color.x*reflectColor.x,color.y*reflectColor.y,color.z*reflectColor.z);
  //color+=reflectColor;
  if (reflectColor.length()>0.0001f) {
    color=color*(1-obj->getReflectivity())+reflectColor*obj->getReflectivity();
    color.normalize();
  }
  return color;
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  glBegin(GL_POINTS);
  for (int i=0;i<IMAGE_WIDTH;++i) {
    for (int j=0;j<IMAGE_HEIGHT;++j) {
      double x=-SCENE_WIDTH/2.0 + double(SCENE_WIDTH)/IMAGE_WIDTH*i;
      double y=-SCENE_HEIGHT/2.0 + double(SCENE_HEIGHT)/IMAGE_HEIGHT*j;
      GVector3 pixel(x,y,0);
      GVector3 direction=pixel-CameraPosition;
      Ray ray(CameraPosition,direction);
      GVector3 resultColor=Tracer(ray,10,-1);
      glColor3f(resultColor.x,resultColor.y,resultColor.z);
      glVertex3f(i,j,0);
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

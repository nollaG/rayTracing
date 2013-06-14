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
#define IMAGE_HEIGHT 600
#define IMAGE_WIDTH 800
#define SCENE_HEIGHT 60
#define SCENE_WIDTH 80
#define MAX_DISTANCE 1000000
#define TRACE_DEPTH 3
#define EPILSON 0.0001

std::vector<GObject*> object_list;
std::vector<LightSource*> light_list;
GVector3 CameraPosition(0.0f,0.0f,40.0f);
GVector3 globalLight(1.0f,1.0f,1.0f);

double HALF_PIXEL_WIDTH = double(SCENE_WIDTH) / double(IMAGE_WIDTH*2.0f);
double HALF_PIXEL_HEIGHT = double(SCENE_HEIGHT) / double(IMAGE_HEIGHT*2.0f);
double PIXEL_WIDTH = double(SCENE_WIDTH) / double(IMAGE_WIDTH);
double PIXEL_HEIGHT = double(SCENE_HEIGHT) / double(IMAGE_HEIGHT);


void init() {
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  glPointSize(1);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH,GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  
  glDepthFunc(GL_LEQUAL);
  GObject *test;
  test=new GSphere(GVector3(-5.0f,-2.0f,5.0f),5.0f);
  test->setKa(GVector3(0.5f,0.0f,0.0f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setShininess(30.0f);
  test->setReflectivity(0.0f);
  test->setTransparency(0.7f);
  object_list.push_back(test);
  test=new GSphere(GVector3(5.0f,5.0f,-5.0f),4.0f);
  test->setShininess(70.0f);
  test->setKa(GVector3(0.5f,0.5f,0.0f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setReflectivity(0.5f);
  test->setTransparency(0.0f);
  object_list.push_back(test);
  test=new GSphere(GVector3(-20.0f,5.0f,0.0f),4.0f);
  test->setShininess(50.0f);
  test->setKa(GVector3(0.3f,0.3f,0.3f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setReflectivity(0.5f);
  test->setTransparency(0.0f);
  object_list.push_back(test);
  test=new GSphere(GVector3(15.0f,5.0f,2.0f),3.0f);
  test->setShininess(50.0f);
  test->setKa(GVector3(0.2f,0.0f,0.4f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setReflectivity(0.6f);
  test->setTransparency(0.0f);
  object_list.push_back(test);
  test=new GFlat(GVector3(0.0f,1.0f,0.0f),GVector3(0.0f,-10.0f,0.0f));
  test->setKa(GVector3(0.5f,0.5f,0.5f));
  test->setKd(GVector3(0.0f,0.2f,0.4f));
  test->setKs(GVector3(0.3f,0.0f,0.0f));
  test->setShininess(0.0f);
  test->setReflectivity(0.5f);
  test->setTransparency(0.0f);
  object_list.push_back(test);
  PointLight* pl=new PointLight();
  pl->setPosition(GVector3(5.0f,15.0f,20.0f));
  pl->setKa(GVector3(1.0f,1.0f,1.0f));
  pl->setKd(GVector3(0.0f,0.0f,1.0f));
  pl->setKs(GVector3(1.0f,1.0f,1.0f));
  light_list.push_back(pl);
  //pl=new PointLight();
  //pl->setPosition(GVector3(-5.0f,50.0f,-20.0f));
  //pl->setKa(GVector3(0.5f,0.5f,0.5f));
  //pl->setKd(GVector3(0.5f,0.5f,0.5f));
  //pl->setKs(GVector3(1.0f,1.0f,1.0f));
  //light_list.push_back(pl);
  //DirectionalLight* dl=new DirectionalLight();
  //dl->setDirection(GVector3(-1.0f,-5.0f,-4.0f));
  //dl->setKa(GVector3(1.0f,1.0f,1.0f));
  //dl->setKd(GVector3(0.0f,0.0f,1.0f));
  //dl->setKs(GVector3(1.0f,1.0f,1.0f));
  //light_list.push_back(dl);
}

GVector3 Tracer(const Ray& ray,int left) {
  GVector3 color(0.0f,0.0f,0.0f);//background
  double distance = MAX_DISTANCE;
  double shade=1.0f;
  int IntersectionObject=-1;
  INTERSECTION_TYPE tmp;
  for (int k=0;k<object_list.size();++k) {
    GObject* obj=object_list.at(k);
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
  GVector3 objMaterial=obj->getKa();
  color=GVector3(globalLight.x*objMaterial.x,globalLight.y*objMaterial.y,globalLight.z*objMaterial.z);
  for (int k=0;k<light_list.size();++k) {
    LightSource* ls = light_list.at(k);
    bool flag=true;
    GVector3 testRayDirection=ls->getLightDirection(point)*(-1.0f);
    GVector3 tracePoint=point;
    while (flag && shade >= EPILSON) {
      flag=false;
      Ray testRay(tracePoint+testRayDirection*EPILSON,testRayDirection);
      int tmpIntersectionObject=-1;
      distance=MAX_DISTANCE;
      for (int k=0;k<object_list.size();++k) {
        GObject* obj=object_list.at(k);
        if ((tmp=obj->isIntersected(testRay,distance))!=MISS) {
          tmpIntersectionObject=k;
        }
      }
      if (tmpIntersectionObject!=-1) {
        shade*=object_list.at(tmpIntersectionObject)->getTransparency();
        tracePoint=testRay.getPoint(distance);
        flag=true;
      }
    }
    if (shade<EPILSON)
      shade=0.0f;
    tmpColor = ls->calColor(obj,point,CameraPosition);
    tmpColor*=shade;
    color += tmpColor;
    //color.normalize();
  }
  if (left==0)
    return color;
  GVector3 normal=obj->getNormal(point);
  normal.normalize();
  GVector3 rd=ray.getDirection();
  GVector3 transparentRayDirection=rd;
  Ray transparentRay(point+transparentRayDirection*EPILSON,transparentRayDirection);
  GVector3 transparentColor=Tracer(transparentRay,left-1);
  //reflect
  GVector3 reflectRayDirection=rd-normal*(rd*normal)*2.0f;
  Ray reflectRay(point+reflectRayDirection*EPILSON,reflectRayDirection);
  GVector3 reflectColor=Tracer(reflectRay,left-1);

  //color=color*(1-obj->getReflectivity())+GVector3(material.x*reflectColor.x,material.y*reflectColor.y,material.z*reflectColor.z)*obj->getReflectivity();
  color=color*(1-obj->getReflectivity()-obj->getTransparency())+GVector3(objMaterial.x*reflectColor.x,objMaterial.y*reflectColor.y,objMaterial.z*reflectColor.z)*obj->getReflectivity()+GVector3(objMaterial.x*transparentColor.x,objMaterial.y*transparentColor.y,objMaterial.z*transparentColor.z)*obj->getTransparency();

  return color;
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  glBegin(GL_POINTS);
  for (int i=0;i<IMAGE_WIDTH;++i) {
    for (int j=0;j<IMAGE_HEIGHT;++j) {
      double left_bottom_x=-SCENE_WIDTH/2.0 + PIXEL_WIDTH*i;
      double left_bottom_y=-SCENE_HEIGHT/2.0 + PIXEL_HEIGHT*j;
      double left_top_x=-SCENE_WIDTH/2.0 + PIXEL_WIDTH*i;
      double left_top_y=-SCENE_HEIGHT/2.0 + PIXEL_HEIGHT*(j+1);
      double right_bottom_x=-SCENE_WIDTH/2.0 + PIXEL_WIDTH*(i+1);
      double right_bottom_y=-SCENE_HEIGHT/2.0 + PIXEL_HEIGHT*j;
      double right_top_x=-SCENE_WIDTH/2.0 + PIXEL_WIDTH*(i+1);
      double right_top_y=-SCENE_HEIGHT/2.0 + PIXEL_HEIGHT*(j+1);
      double center_x=left_bottom_x+HALF_PIXEL_WIDTH;
      double center_y=left_bottom_y+HALF_PIXEL_HEIGHT;
      GVector3 pixel,direction,resultColor;
      Ray ray;
      pixel=GVector3(left_bottom_x,left_bottom_y,0);
      direction=pixel-CameraPosition;
      ray=Ray(CameraPosition,direction);
      resultColor+=Tracer(ray,TRACE_DEPTH);
      pixel=GVector3(left_top_x,left_top_y,0);
      direction=pixel-CameraPosition;
      ray=Ray(CameraPosition,direction);
      resultColor+=Tracer(ray,TRACE_DEPTH);
      pixel=GVector3(right_bottom_x,right_bottom_y,0);
      direction=pixel-CameraPosition;
      ray=Ray(CameraPosition,direction);
      resultColor+=Tracer(ray,TRACE_DEPTH);
      pixel=GVector3(right_top_x,right_top_y,0);
      direction=pixel-CameraPosition;
      ray=Ray(CameraPosition,direction);
      resultColor+=Tracer(ray,TRACE_DEPTH);
      pixel=GVector3(center_x,center_y,0);
      direction=pixel-CameraPosition;
      ray=Ray(CameraPosition,direction);
      resultColor+=Tracer(ray,TRACE_DEPTH);
      resultColor*=0.2;
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

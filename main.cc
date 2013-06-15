#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <stdio.h>
#include "inc/GVector3.h"
#include "inc/GFlat.h"
#include "inc/GSphere.h"
#include "inc/GObject.h"
#include "inc/LightSource.h"
#include "inc/DirectionalLight.h"
#include "inc/PointLight.h"
#include "inc/GComplexModel.h"
#ifdef MULTITHREAD
#include <pthread.h>
#define MULTI_THREAD_NUM 4
#define MULTI_THREAD_TRUNK_SIZE 1000
#endif
#define IMAGE_HEIGHT 600
#define IMAGE_WIDTH 800
#define SCENE_HEIGHT 60
#define SCENE_WIDTH 80
#define MAX_DISTANCE 1000000
#define TRACE_DEPTH 3
#define EPILSON 0.0001
#define BUNNY_VERTICES 453
#define BUNNY_FACES 948

std::vector<GObject*> object_list;
std::vector<LightSource*> light_list;
GVector3 CameraPosition(0.0f,0.0f,60.0f);
GVector3 globalLight(1.0f,1.0f,1.0f);

double HALF_PIXEL_WIDTH = double(SCENE_WIDTH) / double(IMAGE_WIDTH*2.0f);
double HALF_PIXEL_HEIGHT = double(SCENE_HEIGHT) / double(IMAGE_HEIGHT*2.0f);
double PIXEL_WIDTH = double(SCENE_WIDTH) / double(IMAGE_WIDTH);
double PIXEL_HEIGHT = double(SCENE_HEIGHT) / double(IMAGE_HEIGHT);
GVector3 Tracer(const Ray& ray,int left);
void print_progress(int);
int percent;
#ifdef MULTITHREAD
GVector3 pixelColor[IMAGE_WIDTH][IMAGE_HEIGHT];
pthread_mutex_t multi_thread_mutex;
int multithread_pixel;
#endif


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

#ifdef MULTITHREAD
  std::cout << "Multi Thread [ Enabled ]" << std::endl;
#else
  std::cout << "Multi Thread [ Disabled ]" << std::endl;
#endif

#ifdef MULTIRAY
  std::cout << "Multi Ray [ Enabled ]" << std::endl;
#else
  std::cout << "Multi Ray [ Disabled ]" << std::endl;
#endif
#ifdef BUNNY
  GComplexModel* gcm=new GComplexModel();
  FILE* datain=fopen("data/bunny.data","r");
  fprintf(stdout,"Reading data from data/bunny.data\n");
  if (!datain) {
    perror("Open Data File Error");
    exit(1);
  }
  double xx,yy,zz,t1,t2;
  for (int i=0;i<BUNNY_VERTICES;++i) {
    fscanf(datain,"%lf %lf %lf %lf %lf",&xx,&yy,&zz,&t1,&t2);
    xx*=50;
    yy*=50;
    zz*=50;
    gcm->vertices.push_back(GVector3(xx,yy,zz)+GVector3(-6.2f,-5.0f,5.0f));
  }
  int t,a,b,c;
  for (int i=0;i<BUNNY_FACES;++i) {
    fscanf(datain,"%d %d %d %d",&t,&a,&b,&c);
    gcm->indices.push_back(a);
    gcm->indices.push_back(b);
    gcm->indices.push_back(c);
  }
  fclose(datain);
  fprintf(stdout,"Reading Data Done.\n");
  if (gcm->calSurround())
    fprintf(stdout,"surround Calculated.\n");
  gcm->setKa(GVector3(0.5f,0.0f,0.5f));
  gcm->setKd(GVector3(0.3f,0.3f,0.3f));
  gcm->setKs(GVector3(1.0f,1.0f,1.0f));
  gcm->setShininess(40.0f);
  gcm->setReflectivity(0.0f);
  gcm->setTransparency(0.0f);
  object_list.push_back(gcm);
#else
  test=new GSphere(GVector3(3.0f,5.0f,5.0f),4.0f);
  test->setKa(GVector3(0.5f,0.0f,0.5f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setShininess(30.0f);
  test->setReflectivity(0.4f);
  test->setTransparency(0.0f);
  object_list.push_back(test);
#endif
  test=new GSphere(GVector3(-2.0f,0.4f,15.0f),5.0f);
  test->setKa(GVector3(0.5f,0.0f,0.0f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setShininess(30.0f);
  test->setReflectivity(0.0f);
  test->setTransparency(0.7f);
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
  test->setShininess(70.0f);
  test->setKa(GVector3(0.5f,0.5f,0.0f));
  test->setKd(GVector3(0.3f,0.3f,0.3f));
  test->setKs(GVector3(1.0f,1.0f,1.0f));
  test->setReflectivity(0.5f);
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
  pl=new PointLight();
  pl->setPosition(GVector3(-5.0f,50.0f,-20.0f));
  pl->setKa(GVector3(0.5f,0.5f,0.5f));
  pl->setKd(GVector3(0.5f,0.5f,0.5f));
  pl->setKs(GVector3(1.0f,1.0f,1.0f));
  light_list.push_back(pl);
  //DirectionalLight* dl=new DirectionalLight();
  //dl->setDirection(GVector3(-1.0f,-5.0f,-4.0f));
  //dl->setKa(GVector3(1.0f,1.0f,1.0f));
  //dl->setKd(GVector3(0.0f,0.0f,1.0f));
  //dl->setKs(GVector3(1.0f,1.0f,1.0f));
  //light_list.push_back(dl);
}

GVector3 samplePixel(int i,int j) {
  double left_bottom_x=-SCENE_WIDTH/2.0 + PIXEL_WIDTH*i;
  double left_bottom_y=-SCENE_HEIGHT/2.0 + PIXEL_HEIGHT*j;
#ifdef MULTIRAY
  double left_top_x=-SCENE_WIDTH/2.0 + PIXEL_WIDTH*i;
  double left_top_y=-SCENE_HEIGHT/2.0 + PIXEL_HEIGHT*(j+1);
  double right_bottom_x=-SCENE_WIDTH/2.0 + PIXEL_WIDTH*(i+1);
  double right_bottom_y=-SCENE_HEIGHT/2.0 + PIXEL_HEIGHT*j;
  double right_top_x=-SCENE_WIDTH/2.0 + PIXEL_WIDTH*(i+1);
  double right_top_y=-SCENE_HEIGHT/2.0 + PIXEL_HEIGHT*(j+1);
  double center_x=left_bottom_x+HALF_PIXEL_WIDTH;
  double center_y=left_bottom_y+HALF_PIXEL_HEIGHT;
#endif //multiray
  GVector3 pixel,direction,resultColor;
  Ray ray;
  pixel=GVector3(left_bottom_x,left_bottom_y,0);
  direction=pixel-CameraPosition;
  ray=Ray(CameraPosition,direction);
  resultColor+=Tracer(ray,TRACE_DEPTH);
#ifdef MULTIRAY
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
#endif //multiray
  return resultColor;
}


#ifdef MULTITHREAD
void* pthread_helper(void* arg) {
  int tmp;
  int currentInt;
  bool flag;
  while (true) {
    flag=false;
    pthread_mutex_lock(&multi_thread_mutex);
    tmp=multithread_pixel;
    multithread_pixel+=MULTI_THREAD_TRUNK_SIZE;
    currentInt=(tmp+1)*20/(IMAGE_HEIGHT*IMAGE_WIDTH);
    if (currentInt>percent) {
      percent=currentInt;
      flag=true;
    }
    pthread_mutex_unlock(&multi_thread_mutex);
    if (flag)
      print_progress(percent);
    if (tmp>=IMAGE_HEIGHT*IMAGE_WIDTH)
      pthread_exit(0);
    for (int k=0;k<MULTI_THREAD_TRUNK_SIZE;++k) {
      int i=(tmp+k) / IMAGE_HEIGHT;
      int j=(tmp+k) % IMAGE_HEIGHT;
      pixelColor[i][j]=samplePixel(i,j);
    }
  }
}
#endif

void print_progress(int k) {
  for (int i=0;i<k;++i)
    std::cout << "=";
  std::cout << "> " << k*5 << "%" << std::endl;
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
  percent=0;
#ifdef MULTITHREAD
  multithread_pixel = 0;
  pthread_t tid[MULTI_THREAD_NUM];
  for (int i=0;i<MULTI_THREAD_NUM;++i) {
    pthread_create(&tid[i],NULL,pthread_helper,NULL);
  }
  for (int i=0;i<MULTI_THREAD_NUM;++i) {
    pthread_join(tid[i],NULL);
  }
  for (int i=0;i<IMAGE_WIDTH;++i) {
    for (int j=0;j<IMAGE_HEIGHT;++j) {
      glColor3f(pixelColor[i][j].x,pixelColor[i][j].y,pixelColor[i][j].z);
      glVertex3f(i,j,0);
    }
  }

#else
  int currentInt;
  for (int i=0;i<IMAGE_WIDTH;++i) {
    for (int j=0;j<IMAGE_HEIGHT;++j) {
      currentInt=(i*IMAGE_HEIGHT+j+1)*20/(IMAGE_WIDTH*IMAGE_HEIGHT);
      if (currentInt>percent) {
        percent=currentInt;
        print_progress(currentInt);
      }
      GVector3 resultColor=samplePixel(i,j);
      glColor3f(resultColor.x,resultColor.y,resultColor.z);
      glVertex3f(i,j,0);
    }
  }
#endif //multithread
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

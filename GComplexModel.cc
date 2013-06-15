#include <map>
#include <cstdlib>
#include <iostream>
#include "inc/GComplexModel.h"


bool GComplexModel::calSurround() {
  GVector3 surroundCenter;
  double diameter;
  double maxx=-1000.0f,maxy=-1000.0f,maxz=-1000.0f,minx=1000.0f,miny=1000.0f,minz=1000.0f;
  if (vertices.empty())
    return false;
  for (int i=0;i<vertices.size();++i) {
    if (vertices.at(i).x>maxx)
      maxx=vertices.at(i).x;
    if (vertices.at(i).y>maxy)
      maxy=vertices.at(i).y;
    if (vertices.at(i).z>maxz)
      maxz=vertices.at(i).z;
    if (vertices.at(i).x<minx)
      minx=vertices.at(i).x;
    if (vertices.at(i).y<miny)
      miny=vertices.at(i).y;
    if (vertices.at(i).z<minz)
      minz=vertices.at(i).z;
  }
  GVector3 p1(minx,miny,minz);
  GVector3 p2(maxx,maxy,maxz);
  diameter=(p2-p1).length();
  surroundCenter=(p2+p1)*0.5;
  surround.setCenter(surroundCenter);
  surround.setRadius(diameter);
  return true;
}

GVector3 GComplexModel::getNormal(const GVector3& p) const {
  std::map<GVector3,GVector3>::const_iterator iter;
  iter=normals_map.find(p);
  if (iter!=normals_map.end()) {
    return iter->second;
  }  else {
    std::cout << "Panic!We can not Find!\n" << std::endl;;
    exit(1);
  }
}

GVector3 GComplexModel::calNormal(const GVector3& v0,const GVector3& v1,const GVector3& v2) const {
  GVector3 t1=v1-v0;
  GVector3 t2=v2-v1;
  return t1.cross(t2);
}

bool GComplexModel::intersectTriangle(const Ray& ray,const GVector3& v0,const GVector3& v1,const GVector3& v2,double &dist,GVector3& normal) {
  GVector3 E1=v1-v0;
  GVector3 E2=v2-v0;
  GVector3 P = ray.getDirection().cross(E2);
  double det = E1*P;
  GVector3 T;
  if (det > 0) {
    T = ray.getOrigin() -v0;
  }
  else {
    T = v0 - ray.getOrigin();
    det = -det;
  }

  if (det < 0.0001f) {
    return false;

  }
  double u = T*P;
  if (u<0.0f || u > det) {
    return false;
  }
  GVector3 Q = T.cross(E1);
  double v=ray.getDirection()*Q;
  if (v < 0.0f || u+v > det) {
    return false;
  }
  double t=E2*Q;
  double fInvDet = 1.0f / det;
  if (t<0)
    return false;
  if (t*fInvDet < dist) {
    dist = t*fInvDet;
    normal=calNormal(v0,v1,v2);
    return true;
  } else {
    return false;
  }
}

INTERSECTION_TYPE GComplexModel::isIntersected(const Ray& ray,double &dist) {
  double tmpdist=dist;
  if (surround.isIntersected(ray,tmpdist)==MISS)
    return MISS;
  bool result=false;
  GVector3 tmpnormal;
  for (int i=0;i<indices.size();i+=3) {
    if (intersectTriangle(ray,vertices.at(indices.at(i)),
          vertices.at(indices.at(i+1)),
            vertices.at(indices.at(i+2)),
            dist,tmpnormal)) {
      result=true;
    }
  }
  if (result) {
    GVector3 p=ray.getPoint(dist);
    std::map<GVector3,GVector3>::const_iterator iter;
    iter=normals_map.find(p);
    if (iter==normals_map.end()) {
      normals_map.insert(std::pair<GVector3,GVector3>(p,tmpnormal));
    }
      return INTERSECTED_OUT;
  }
  else
    return MISS;
}

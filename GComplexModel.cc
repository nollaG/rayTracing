#include "inc/GComplexModel.h"

bool GComplexModel::calSurround() {
  GVector3 surroundCenter;
  double diameter=-1.0f;
  for (int i=0;i<vertices.size();++i)
    for (int j=i+1;j<vertices.size();++j) {
      GVector3 tmp=vertices.at(j)-vertices.at(i);
      if (tmp.length()>diameter) {
        diameter=tmp.length();
        surroundCenter=(vertices.at(i)+vertices.at(j))*0.5;
      }
    }
  if (diameter<0)
    return false;
  surround.setCenter(surroundCenter);
  surround.setRadius(diameter*0.5);
  return true;
}

GVector3 GComplexModel::getNormal(const GVector3& p) const {
  return tmpNormal;
}

GVector3 GComplexModel::calNormal(const GVector3& v0,const GVector3& v1,const GVector3& v2) const {
  GVector3 t1=v1-v0;
  GVector3 t2=v2-v1;
  return t1.cross(t2);
}

bool GComplexModel::intersectTriangle(const Ray& ray,const GVector3& v0,const GVector3& v1,const GVector3& v2,double &dist) {
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

  if (det < 0.0001f)
    return false;
  double u = T*P;
  if (u<0.0f || u > det)
    return false;
  GVector3 Q = T.cross(E1);
  double v=ray.getDirection()*Q;
  if (v < 0.0f || u+v > det) {
    return false;
  }
  double t=E2*Q;
  double fInvDet = 1.0f / det;
  if (t*fInvDet < dist) {
    dist = t*fInvDet;
    tmpNormal=calNormal(v0,v1,v2);
    return true;
  } else {
    return false;
  }
}

INTERSECTION_TYPE GComplexModel::isIntersected(const Ray& ray,double &dist) {
  bool result=false;
  for (int i=0;i<indices.size();i+=3) {
    if (intersectTriangle(ray,vertices.at(indices.at(i)),
          vertices.at(indices.at(i+1)),
            vertices.at(indices.at(i+2)),
            dist)) {
      result=true;
    }
  }
  if (result)
    return INTERSECTED_OUT;
  else
    return MISS;
}

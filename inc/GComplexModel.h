#ifndef GCOMPLEXMODEL_H
#define GCOMPLEXMODEL_H
#include <vector>
#include "GSphere.h"
#include "GObject.h"

class GComplexModel:public GObject {
  private:
    GSphere surround;
    GVector3 tmpNormal;//use to get normal,will fix it in future
  private:
    bool intersectTriangle(const Ray& ray,const GVector3& v0,const GVector3& v1,const GVector3&v2,double& dist);
    GVector3 calNormal(const GVector3& v0,const GVector3& v1,const GVector3&v2) const;
  public:
    std::vector<GVector3> vertices;
    std::vector<int> indices; //every 3 a face

  public:
    bool calSurround();

    GVector3 getNormal(const GVector3&) const;
    INTERSECTION_TYPE isIntersected(const Ray& ray,double& dist);

};

#endif /* end of include guard: GCOMPLEXMODEL_H */


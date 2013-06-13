#include <cmath>
#include "inc/GObject.h"
#include "inc/PointLight.h"


GVector3 PointLight::calAmbient(const GVector3& material_Ka) const {
  return GVector3(m_Ka.x*material_Ka.x,
      m_Ka.y*material_Ka.y,
      m_Ka.z*material_Ka.z
      );
}

GVector3 PointLight::calDiffuse(const GVector3& material_Kd,const GVector3& normal,const GVector3& rayDirection) const {
  GVector3 IdKd(m_Kd.x*material_Kd.x,
      m_Kd.y*material_Kd.y,
      m_Kd.z*material_Kd.z
      );
  double normalDotRay = normal*rayDirection;
  if (normalDotRay < 0.0f)
    normalDotRay=0.0f;
  return IdKd*normalDotRay;
}

GVector3 PointLight::calSpecular(const GVector3& material_Ks,const GVector3& normal,const GVector3& rayDirection,const GVector3& cameraDirection,double material_shinness) const {
  GVector3 IsKs(m_Ks.x*material_Ks.x,
      m_Ks.y*material_Ks.y,
      m_Ks.z*material_Ks.z
      );
  GVector3 H = cameraDirection+rayDirection;
  H.normalize();
  double normalDotRay = normal*rayDirection;
  if (normalDotRay < 0.0f)
    normalDotRay=0.0f;
  double normalDotH = normal*H;
  if (normalDotH < 0.0f)
    normalDotH = 0.0f;
  double normalDotHPowShinness=pow(normalDotH,material_shinness);
  if (normalDotRay <= 0.0f)
    normalDotHPowShinness=0.0f;
  return IsKs*normalDotHPowShinness;
}

GVector3 PointLight::calColor(const GObject* obj,const GVector3& point,const GVector3& cameraPosition) const {
  GVector3 color(0.0f,0.0f,0.0f);
  GVector3 normal=obj->getNormal(point);
  normal.normalize();
  GVector3 ambient = calAmbient(obj->getKa());
  GVector3 rayDirection = this->getPosition() - point;
  rayDirection.normalize();
  GVector3 diffuse = calDiffuse(obj->getKd(),normal,rayDirection);
  GVector3 cameraDirection = cameraPosition - point;
  cameraDirection.normalize();
  GVector3 specular = calSpecular(obj->getKs(),normal,rayDirection,cameraDirection,obj->getShininess());
  color = ambient + diffuse + specular;
  return color;
}

GVector3 PointLight::getLightDirection(const GVector3& point) const {
  return point-this->getPosition();
}

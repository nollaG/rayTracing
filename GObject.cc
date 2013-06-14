#include "inc/GObject.h"

GObject::GObject():m_Shininess(0.0f),m_Reflectivity(0.0f){}

GObject::GObject(const GVector3& ka,const GVector3& kd,const GVector3& ks,double shi,double ref,double tra):
  m_Ka(ka),m_Kd(kd),m_Ks(ks),m_Shininess(shi),m_Reflectivity(ref),m_Transparency(tra){}

void GObject::setKa(const GVector3& ka) {
  m_Ka=ka;
}

void GObject::setKd(const GVector3& kd) {
  m_Kd=kd;
}

void GObject::setKs(const GVector3& ks) {
  m_Ks=ks;
}
 void GObject::setShininess(double shi) {
   m_Shininess=shi;
 }

void GObject::setReflectivity(double ref) {
  m_Reflectivity=ref;
}
void GObject::setTransparency(double tra) {
  m_Transparency=tra;
}

GVector3 GObject::getKa() const {
  return m_Ka;
}
GVector3 GObject::getKd() const {
  return m_Kd;
}

GVector3 GObject::getKs() const {
  return m_Ks;
}

double GObject::getShininess() const {
  return m_Shininess;
}

double GObject::getReflectivity() const {
  return m_Reflectivity;
}
double GObject::getTransparency() const {
  return m_Transparency;
}

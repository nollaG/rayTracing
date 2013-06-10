#include "inc/GVector3.h"
#include <cmath>
#include <iostream>

GVector3::GVector3():x(0.0f),y(0.0f),z(0.0f){}

GVector3::GVector3(const GVector3& rhs):x(rhs.x),y(rhs.y),z(rhs.z){}

GVector3::GVector3(float xx,float yy,float zz):x(xx),y(yy),z(zz){}

float GVector3::length() const {
  return sqrt(x*x+y*y+z*z);
}



bool GVector3::normalize() {
  float len=this->length();
  if (len==0)
    return false;
  x/=len;
  y/=len;
  z/=len;
  return true;
}
GVector3 GVector3::operator=(const GVector3& rhs) {
  x=rhs.x;
  y=rhs.y;
  z=rhs.z;
  return *this;
}

GVector3 GVector3::operator=(float f) {
  x=f;
  y=f;
  z=f;
  return *this;
}

GVector3 GVector3::operator+(const GVector3& rhs) const {
  GVector3 g1(x+rhs.x,y+rhs.y,z+rhs.z);
  return g1;
}
GVector3 GVector3::operator+=(const GVector3& rhs) {
  x+=rhs.x;
  y+=rhs.y;
  z+=rhs.z;
  return *this;
}
GVector3 GVector3::operator-(const GVector3& rhs) const {
  GVector3 g1(x-rhs.x,y-rhs.y,z-rhs.z);
  return g1;
}
GVector3 GVector3::operator-=(const GVector3& rhs) {
  x-=rhs.x;
  y-=rhs.y;
  z-=rhs.z;
  return *this;
}

GVector3 GVector3::operator*(const float f) const {
  GVector3 g1(x*f,y*f,z*f);
  return g1;
}
GVector3 GVector3::operator*=(const float f) {
  x*=f;
  y*=f;
  z*=f;
  return *this;
}

float GVector3::operator*(const GVector3& rhs) const {
  return x*rhs.x+y*rhs.y+z*rhs.z;
}


GVector3 GVector3::operator/(const float f) const {
  GVector3 g1;
  if (f==0.0f)
    return g1;
  g1.x=x/f;
  g1.y=y/f;
  g1.z=z/y;
  return g1;
}
GVector3 GVector3::operator/=(const float f) {
  if (f==0.0f)
    return *this;
  x/=f;
  y/=f;
  z/=f;
  return *this;
}

std::ostream& operator<<(std::ostream& os,const GVector3& g) {
  os << g.x << " " << g.y << " " << " " <<g.z;
  return os;
}
std::istream& operator>>(std::istream& is,GVector3& g) {
  is >> g.x >> g.y >> g.z;
  return is;
}

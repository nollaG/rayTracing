#ifndef GVECTOR3_H

#define GVECTOR3_H
#include <iostream>

class GVector3 {
  public:  
    float x;
    float y;
    float z;
  public:
    friend std::ostream& operator<<(std::ostream&,const GVector3&);
    friend std::istream& operator>>(std::istream&,GVector3&);
    GVector3();
    GVector3(const GVector3&);
    GVector3(float,float,float);
    float length() const;
    //false if the length==0
    bool normalize();
    GVector3 operator=(const GVector3&);
    GVector3 operator=(float);
    GVector3 operator+(const GVector3&) const;
    GVector3 operator+=(const GVector3&);
    GVector3 operator-(const GVector3&) const;
    GVector3 operator-=(const GVector3&);
    GVector3 operator*(const float) const;
    GVector3 operator*=(const float);
    float operator*(const GVector3&) const;
    GVector3 operator/(const float) const;
    GVector3 operator/=(const float);
};
std::ostream& operator<<(std::ostream&,const GVector3&);
std::istream& operator>>(std::istream&,GVector3&);

#endif /* end of include guard: GVECTOR3_H */

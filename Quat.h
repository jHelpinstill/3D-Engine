#ifndef QUAT_
#define QUAT_

#include "Vec3.h"
#include "Mat4.h"

class Quat
{
public:
  union
  {
    struct { float a, b, c, d; };
    struct { float w, x, y, z; };
    float n[4];
  };

  Quat();
  Quat(float a1, float b1, float c1, float d1);
  Quat(Vec3 v, float deg);
  Quat(Vec3 eulers);
  
  Quat operator*(Quat q);
  Vec3 operator*(Vec3 v);
  Quat inverse();
  
  void convertAxisAngle(Vec3 vin, float angle);
  Quat slerp(float t);
  void normalize();
  
  Vec3 getAxis();
  float getAngle();
  Vec3 eulerAngles();
  Mat4 mat();
  
  void debug_print();
};

#endif

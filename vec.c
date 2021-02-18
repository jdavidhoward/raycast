//David Howard
#include <math.h>
#include "vec.h"

VEC_T normalize(VEC_T v) {

    double mag = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

    v.x = v.x / mag;

    v.y = v.y / mag;

    v.z = v.z / mag;

  return v;
}

 double dot(VEC_T v1, VEC_T v2) {

 return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

}

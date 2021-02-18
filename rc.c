//David Howard
//March 26, 2018
// Computer Organization CSCI 304
//This is a program that creates an image using raycasting.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rc.h"

void read_objs(OBJ_T **list) {

//Variable declaration
  double center_x,
         center_y,
         center_z,
         radius,
         r,
         g,
         b;

  OBJ_T *new;

  while (scanf("%lf %lf %lf %lf %lf %lf %lf", &center_x, &center_y, &center_z, &radius, &r, &g, &b) == 7)
  {
      new = (OBJ_T *)malloc(sizeof(OBJ_T));
      new->sphere.center.x = center_x;
      new->sphere.center.y = center_y;
      new->sphere.center.z = center_z;
      new->sphere.radius = radius;
      new->color.r = r;
      new->color.g = g;
      new->color.b = b;
      new->next = *list;
      *list = new;
    }
}

int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t) {

 //Variable declaration
  double A, B, C;

  A = 1;

  B = 2 *    ((ray.direction.x * (ray.origin.x - sphere.center.x)) +
             (ray.direction.y * (ray.origin.y - sphere.center.y)) +
             (ray.direction.z * (ray.origin.z - sphere.center.z)));

  C =   ((ray.origin.x - sphere.center.x) * (ray.origin.x - sphere.center.x)) +
        ((ray.origin.y - sphere.center.y) * (ray.origin.y - sphere.center.y)) +
        ((ray.origin.z - sphere.center.z) * (ray.origin.z - sphere.center.z)) -
        (sphere.radius * sphere.radius);

  double discriminant = (B * B) - 4*A*C;

    if (discriminant < 0) {
        return 0;
    }

  float t_0 = (-B + sqrt(discriminant)) / 2*A;

  float t_1 = (-B - sqrt(discriminant)) / 2*A;

  if (t_0 < 0 && t_1 < 0) {
      return 0;
  }

  *t = t_0 < t_1 ? t_0 : t_1;

  return 1;
}

COLOR_T cast(RAY_T ray, OBJ_T *list) {

//Variable declaration
      OBJ_T *curr;
      double min_t = 1000;

      double t;

      COLOR_T color;

      color.r = 1.;

      color.g = 1.;

      color.b = 1.;

      for (curr = list; curr != NULL; curr = curr->next) {

          if (intersect_sphere(ray, curr->sphere, &t)) {

              if (t < min_t) {

                  color = curr->color;

                  min_t = t;
            }
        }
    }
    return color;
}

int main() {

//Variable declaration
  OBJ_T *list = NULL;

  OBJ_T *curr;

  read_objs(&list);

  COLOR_T pixel;

  RAY_T ray;

  double t;

  int x, y;

  ray.origin.x = 0, ray.origin.y = 0, ray.origin.z = 0;

  ray.direction.z = 1;

// PPM imgage header
  printf("P6\n1000 1000\n255\n");

//Running through the pixels in the image file.
  for (y = 0; y < 1000; y++) {

      for (x = 0; x < 1000; x++) {

          ray.direction.x = -0.5 + x / 1000.0;

          ray.direction.y = 0.5 - y / 1000.0;

          ray.direction = normalize(ray.direction);

          curr = list;

          pixel = cast(ray, list);

          printf("%c%c%c", (unsigned char)(pixel.r * 255),
                           (unsigned char)(pixel.g * 255),
                           (unsigned char)(pixel.b * 255));

        }
    }

    while (list != NULL) {

      curr = list;

      list = list->next;

      free(curr);
    }
}

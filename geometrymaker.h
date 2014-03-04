#ifndef GEOMETRYMAKER_H
#define GEOMETRYMAKER_H

#include <cmath>
#include <iostream>
#include <vector>

#include "cvec.h"

//--------------------------------------------------------------------------------
// Helpers for creating some special geometries such as plane, cubes, and spheres
//--------------------------------------------------------------------------------


// A generic vertex structure containing position, normal, and texture information
// Used by make* functions to pass vertex information to the caller
struct GenericVertex {
  Cvec3f pos;
  Cvec3f normal;
  Cvec2f tex;
  Cvec3f tangent, binormal;

  GenericVertex(
    float x, float y, float z,
    float nx, float ny, float nz,
    float tu, float tv,
    float tx, float ty, float tz,
    float bx, float by, float bz)
    : pos(x,y,z), normal(nx,ny,nz), tex(tu, tv), tangent(tx, ty, tz), binormal(bx, by, bz)
  {}
};

inline void getPlaneVbIbLen(int& vbLen, int& ibLen) {
  vbLen = 4;
  ibLen = 6;
}

template<typename VtxOutIter, typename IdxOutIter>
void makePlane(float size, VtxOutIter vtxIter, IdxOutIter idxIter) {
  float h = size / 2.0;
  *vtxIter = GenericVertex(    -h, 0, -h, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, -1);
  *(++vtxIter) = GenericVertex(-h, 0,  h, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, -1);
  *(++vtxIter) = GenericVertex( h, 0,  h, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, -1);
  *(++vtxIter) = GenericVertex( h, 0, -h, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, -1);
  *idxIter = 0;
  *(++idxIter) = 1;
  *(++idxIter) = 2;
  *(++idxIter) = 0;
  *(++idxIter) = 2;
  *(++idxIter) = 3;
}

inline void getCubeVbIbLen(int& vbLen, int& ibLen) {
  vbLen = 24;
  ibLen = 36;
}

template<typename VtxOutIter, typename IdxOutIter>
void makeCube(float size, VtxOutIter vtxIter, IdxOutIter idxIter) {
  float h = size / 2.0;
  Cvec3f tan(0, 1, 0), bin(0, 0, 1);
  { *vtxIter = GenericVertex(+ h, - h, - h, 1, 0, 0, 0, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, + h, - h, 1, 0, 0, 1, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, + h, + h, 1, 0, 0, 1, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, - h, + h, 1, 0, 0, 0, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };

  tan = Cvec3f(0, 0, 1);
  bin = Cvec3f(0, 1, 0);
  { *vtxIter = GenericVertex(- h, - h, - h, -1, 0, 0, 0, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(- h, - h, + h, -1, 0, 0, 1, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(- h, + h, + h, -1, 0, 0, 1, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(- h, + h, - h, -1, 0, 0, 0, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };

  tan = Cvec3f(0, 0, 1);
  bin = Cvec3f(1, 0, 0);
  { *vtxIter = GenericVertex(- h, + h, - h, 0, 1, 0, 0, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(- h, + h, + h, 0, 1, 0, 1, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, + h, + h, 0, 1, 0, 1, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, + h, - h, 0, 1, 0, 0, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };

  tan = Cvec3f(1, 0, 0);
  bin = Cvec3f(0, 0, 1);
  { *vtxIter = GenericVertex(- h, - h, - h, 0, -1, 0, 0, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, - h, - h, 0, -1, 0, 1, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, - h, + h, 0, -1, 0, 1, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(- h, - h, + h, 0, -1, 0, 0, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };

  tan = Cvec3f(1, 0, 0);
  bin = Cvec3f(0, 1, 0);
  { *vtxIter = GenericVertex(- h, - h, + h, 0, 0, 1, 0, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, - h, + h, 0, 0, 1, 1, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, + h, + h, 0, 0, 1, 1, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(- h, + h, + h, 0, 0, 1, 0, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };

  tan = Cvec3f(0, 1, 0);
  bin = Cvec3f(1, 0, 0);
  { *vtxIter = GenericVertex(- h, - h, - h, 0, 0, -1, 0, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(- h, + h, - h, 0, 0, -1, 1, 0, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, + h, - h, 0, 0, -1, 1, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };
  { *vtxIter = GenericVertex(+ h, - h, - h, 0, 0, -1, 0, 1, tan[0], tan[1], tan[2], bin[0], bin[1], bin[2]); ++vtxIter; };

  for (int v = 0; v < 24; v +=4) {
    *idxIter = v;
    *++idxIter = v + 1;
    *++idxIter = v + 2;
    *++idxIter = v;
    *++idxIter = v + 2;
    *++idxIter = v + 3;
    ++idxIter;
  }
}

inline void getOctahedronVbIbLen(int& vbLen, int& ibLen) {
  // TODO
  vbLen = 24;
  ibLen = 24;
}

template<typename VtxOutIter, typename IdxOutIter>
void makeOctahedron(float h, VtxOutIter vtxIter, IdxOutIter idxIter) {

  // TODO
  // Vertices should be (+/-h, 0, 0), (0, +/-h, 0) and (0, 0, +/- h).
  // Normals should point outward and be normal to faces of octahedron.
  
  // Top side
  { *vtxIter = GenericVertex(0, 0, -h, h, h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(h, 0, 0, h, h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, h, 0, h, h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };

  { *vtxIter = GenericVertex(h, 0, 0, h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, h, 0, h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, 0, h, h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };

  { *vtxIter = GenericVertex(-h, 0, 0, -h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, h, 0, -h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, 0, h, -h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };

  { *vtxIter = GenericVertex(-h, 0, 0, -h, h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, 0, -h, -h, h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, h, 0, -h, h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };

  // Bottom Side
  { *vtxIter = GenericVertex(0, 0, -h, h, -h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(h, 0, 0, h, -h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, -h, 0, h, -h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };

  { *vtxIter = GenericVertex(h, 0, 0, h, -h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, -h, 0, h, -h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, 0, h, h, -h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };

  { *vtxIter = GenericVertex(-h, 0, 0, -h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, -h, 0, -h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, 0, h, -h, h, h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };

  { *vtxIter = GenericVertex(-h, 0, 0, -h, -h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, 0, -h, -h, -h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };
  { *vtxIter = GenericVertex(0, -h, 0, -h, -h, -h, 1, 1, 1, 1, 1, 1, 1, 1); ++vtxIter; };


  for (int v = 0; v < 24; v++) {
    *idxIter = v;
    ++idxIter;
  }  

}

inline void getTubeVbIbLen(int slices, int& vbLen, int& ibLen) {
  // TODO
  vbLen = 2 * slices + 2;
  ibLen = 6 * (slices * 2);
}

template<typename VtxOutIter, typename IdxOutIter>
void makeTube(float radius, float height, int slices, VtxOutIter vtxIter, IdxOutIter idxIter) {
  // TODO
  // A hollow cylindrical tube with given radius and height 
  // Normals should point away from the axis of the cylinder
  assert(slices > 1);
  using namespace std;
  
  const double radPerSlice = 2 * CS150_PI / slices;

  vector<double> longSin(slices + 1), longCos(slices + 1);

  for (int i = 0; i < slices + 1; i++) {
    for (int j = 0; j < 2; j++) {
      float x = cos(radPerSlice * i);
      float y = j % 2 == 0 ? -1 * height / 2 : height / 2;
      float z = sin(radPerSlice * i);
      
      *vtxIter = GenericVertex(x * radius, y, z * radius, x, 0, z, 1, 1, 1, 1, 1, 1, 1, 1);
      vtxIter++;

    }
  }

  for (int i = 0; i < (slices * 2); i+= 2) {
    *idxIter = i;
    *++idxIter = i + 1;
    *++idxIter = i + 2;

    *++idxIter = i + 1;
    *++idxIter = i + 2;
    *++idxIter = i + 3;
    ++idxIter;
  }
}

inline void getSphereVbIbLen(int slices, int stacks, int& vbLen, int& ibLen) {
  assert(slices > 1);
  assert(stacks >= 2);
  vbLen = (slices + 1) * (stacks + 1);
  ibLen = slices * stacks * 6;
}

template<typename VtxOutIter, typename IdxOutIter>
void makeSphere(float radius, int slices, int stacks, VtxOutIter vtxIter, IdxOutIter idxIter) {
  using namespace std;
  assert(slices > 1);
  assert(stacks >= 2);

  const double radPerSlice = 2 * CS150_PI / slices;
  const double radPerStack = CS150_PI / stacks;

  vector<double> longSin(slices+1), longCos(slices+1);
  vector<double> latSin(stacks+1), latCos(stacks+1);
  for (int i = 0; i < slices + 1; ++i) {
    longSin[i] = sin(radPerSlice * i);
    longCos[i] = cos(radPerSlice * i);
  }
  for (int i = 0; i < stacks + 1; ++i) {
    latSin[i] = sin(radPerStack * i);
    latCos[i] = cos(radPerStack * i);
  }

  for (int i = 0; i < slices + 1; ++i) {
    for (int j = 0; j < stacks + 1; ++j) {
      float x = longCos[i] * latSin[j];
      float y = longSin[i] * latSin[j];
      float z = latCos[j];

      Cvec3f n(x, y, z);
      Cvec3f b(-longSin[i], longCos[i], 0);
      Cvec3f t = cross(n, b);

      *vtxIter = GenericVertex(
        x * radius, y * radius, z * radius,
        x, y, z,
        1.0/slices*i, 1.0/stacks*j,
        t[0], t[1], t[2],
        b[0], b[1], b[2]);
      ++vtxIter;

      if (i < slices && j < stacks ) {
        *idxIter = (stacks+1) * i + j;
        *++idxIter = (stacks+1) * i + j + 1;
        *++idxIter = (stacks+1) * (i + 1) + j + 1;

        *++idxIter = (stacks+1) * i + j;
        *++idxIter = (stacks+1) * (i + 1) + j + 1;
        *++idxIter = (stacks+1) * (i + 1) + j;
        ++idxIter;
      }
    }
  }
}

#endif

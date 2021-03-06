/*
*  Tim Curtis
*  Face.h
*
*  Header file for the Face class.
*/

#include "Material.h"
#include <list>

class Face {
public:
  Face() {}
  ~Face() {}

  list<int> vIndexes;     // These two vectors will hold vertex and normal
  list<int> nIndexes;     // information for the face
  list<int> tIndexes;
  int mat;                // Represents index of material to be used
};

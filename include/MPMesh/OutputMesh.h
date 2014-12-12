/// \author Kacey Coley
/// \date December 11, 2014
/// \since 0.1
///
/// Abstract Base Class for writing mesh data
///
///   Copyright 2014 Kacey Coley
///   Licensed under the Apache License, Version 2.0 (the "License");
///   you may not use this file except in compliance with the License.
///   You may obtain a copy of the License at
///
///   http://www.apache.org/licenses/LICENSE-2.0
///
///   Unless required by applicable law or agreed to in writing, software
///   distributed under the License is distributed on an "AS IS" BASIS,
///   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
///   See the License for the specific language governing permissions and
///   limitations under the License.
///

#ifndef __OUTPUTMESH_H__
#define __OUTPUTMESH_H__

#include <string>
#include <list>
#include <vector>
#include "MPPlugins/defines.h"
#include"MPPlugins/pluginapi.h"
#include "MeshPotato/meshpotato.h"
#include "MPUtils/AttributeTable.h"

namespace MeshPotato{
 namespace MPMesh {
   /**
   * \brief OutputMesh is the Abstract Base Class for writing Mesh Formats.
   *
   * OutputMesh retrieves the vertices, normals and faces from a mesh format.
   * The faces can be an arbitrary n-gon planar.
   **/
    class OutputMesh {
    public:
        virtual ~OutputMesh() {}
        virtual bool loadMesh(
      	     const std::list<std::vector<std::string> > &vertices,
      	     const std::list<std::vector<std::string> > &normals,
      	     const std::list<std::vector<std::string> > &faces,
      	     const MPUtils::AttributeTable &table = MPUtils::AttributeTable()
        ) = 0;
      	virtual const char * getName() const = 0;
      	virtual bool writeMesh(const char *name) = 0;
      	virtual const unsigned int getNumberVertices() const = 0;
      	virtual const unsigned int getNumberNormals() const = 0;
      	virtual const unsigned int getNumberFaces() const = 0;
    };
 } // namespace MPMesh
} // namespace MeshPotato

#endif// __OUTPUTMESH_H__

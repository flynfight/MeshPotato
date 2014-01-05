#include <boost/python.hpp>
#include "OBJInputPlugin.h"
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <list>
#include <vector>
using namespace boost::python;
using namespace MyEngine;
struct InputMeshWrap: MyEngine::InputMesh, wrapper<MyEngine::InputMesh> {
        void loadMesh(const char *) {}
        void writeMesh(const char *) {}
        const size_t getNumberVertices() const {
                return this->get_override("getNumberVertices")();
        }

};

BOOST_PYTHON_MODULE(pyOBJInputPlugin) {
//        openvdb::initialize();
        class_<InputMeshWrap, boost::noncopyable>("InputMesh")
                .def("loadMesh", pure_virtual(&MyEngine::InputMesh::InputMeshDriver::loadMesh))
                .def("getNumberVertices", pure_virtual(&MyEngine::InputMesh::InputMeshDriver::getNumberVertices))
                ;
	class_<OBJInputMeshDriver, bases<InputMeshWrap> >("OBJInputMesh")
		.def("loadMesh", &OBJInputMeshDriver::loadMesh)
		.def("getNumberVertices", &OBJInputMeshDriver::getNumberVertices)
		.def("getVertices", &OBJInputMeshDriver::getVertices)
		.def("getNormals", &OBJInputMeshDriver::getNormals)
		.def("getFaces", &OBJInputMeshDriver::getFaces)
		; 
}

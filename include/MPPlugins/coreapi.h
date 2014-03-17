#ifndef __COREAPI_H__
#define __COREAPI_H__

#include "defines.h"
#include "OutputMeshAPI.h"
#include "InputMeshAPI.h"
#include "MPVolume/MPVolume.h"
#include <string>
#include <map>

///
/// A factory object in the Core API
///
namespace MeshPotato {
namespace MPPlugins {
class CORE_API OutputMeshFactory {
public:
	typedef OutputMeshAPI *(*CreateCallback)();

	static void RegisterOutputMesh(const std::string & type, CreateCallback cb);
	static void UnregisterOutputMesh(const std::string &type);
	static OutputMeshAPI *CreateOutputMesh(const std::string &type);
private:
	typedef std::map<std::string, CreateCallback> CallbackMap;
	static CallbackMap mOutputMeshes;

};

class CORE_API InputMeshFactory {
public:
	typedef InputMeshAPI *(*CreateCallback)();

	static void RegisterInputMesh(const std::string & type, CreateCallback cb);
	static void UnregisterInputMesh(const std::string &type);
	static InputMeshAPI *CreateInputMesh(const std::string &type);
private:
	typedef std::map<std::string, CreateCallback> CallbackMap;
	static CallbackMap mInputMeshes;

};
class CORE_API VolumeFloatFactory {
public:
	typedef MPVolume::VolumeFloatPtr *(*CreateCallback)();

	static void RegisterVolumeFloat(const std::string & type, CreateCallback cb);
	static void UnregisterVolumeFloat(const std::string &type);
	static MPVolume::VolumeFloatPtr *CreateVolumeFloat(const std::string &type);
private:
	typedef std::map<std::string, CreateCallback> CallbackMap;
	static CallbackMap mVolumeFloats;

};

}
}
#endif // __COREAPI_H__
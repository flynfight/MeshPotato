#include "MeshPotato/MPVolume/MPVolume.h"
#include "MeshPotato/MPVolume/FrustumGrid.h"
#include <openvdb/tools/LevelSetRebuild.h>
#include <iostream>
#include <openvdb/version.h>

using namespace std;
namespace MeshPotato {
	namespace MPVolume {
		/// Helper function for reading VDB grids
		openvdb::GridBase::Ptr readVDBGrid(const std::string &vdbFile) {

		openvdb::GridBase::Ptr baseGrid;
                        openvdb::FloatGrid::Ptr grid_i;
                        openvdb::GridPtrVecPtr grids_i(new openvdb::GridPtrVec);
                        static std::string sName("Loading VDB ");
                        openvdb::io::File file_i(vdbFile);
                        file_i.open();
                        openvdb::io::File::NameIterator nameIter = file_i.beginName();
                        baseGrid = file_i.readGrid(nameIter.gridName());

			return baseGrid;

}
/// Helper function for writing VDB grids
		openvdb::FloatGrid::Ptr makeVDBGrid(VolumeFloatPtr &mpgrid, const MeshPotato::MPUtils::BBox& worldBB, double voxelSize) {
			openvdb::FloatGrid::Ptr vdbgrid = openvdb::FloatGrid::create(voxelSize*10);

			openvdb::FloatGrid::Accessor accessor = vdbgrid->getAccessor();
			vdbgrid->transform().preScale(voxelSize);
			vdbgrid->transform().postTranslate(worldBB.min());
			openvdb::Coord max;
			MPUtils::MPVec3 temp  = ((worldBB.max() - worldBB.min())/voxelSize);
			max.x() = (1 + ceil(temp.x()));
			max.y() = (1 + ceil(temp.y()));
			max.z() = (1 + ceil(temp.z()));


			openvdb::Coord min(0,0,0);
			openvdb::CoordBBox indexBB(min,max);
			const float outside = vdbgrid->background();
			const float inside = -outside;
			for (openvdb::Int32 i = indexBB.min().x(); i <= indexBB.max().x(); ++i) {
				for (openvdb::Int32 j = indexBB.min().y(); j <= indexBB.max().y(); ++j) {
					for (openvdb::Int32 k = indexBB.min().z(); k <= indexBB.max().z(); ++k) {
						// transform point (i, j, k) of index space into world space
						MeshPotato::MPUtils::MPVec3 p = vdbgrid->transform().indexToWorld(openvdb::Coord(i,j,k));

						// compute level set function value
						MeshPotato::MPUtils::MPVec3 P(p.x(), p.y(),p.z());
						float value = -mpgrid->eval(P);
						if (value > outside || value < inside) continue;
						accessor.setValue(openvdb::Coord(i, j, k), value);
					}
				}
			}
<<<<<<< HEAD:src/VolumeUtils.C
						
			// In OpenVDB 3.0, signedFloodFill has been moved to openvdb::tools
			// for backwards-compatibility, we check the openvdb version number
			#if OPENVDB_LIBRARY_MAJOR_VERSION_NUMBER <= 2
				vdbgrid->signedFloodFill();
			#else
				openvdb::tools::signedFloodFill(vdbgrid->tree());
			#endif
			// TODO!
			// moved in OpenVDB 3.0 to openvdb::tools.

			openvdb::tools::levelSetRebuild(*vdbgrid);
			vdbgrid->setGridClass(openvdb::GRID_LEVEL_SET);
			return vdbgrid;
		}

		/// Helper function for building frustum cameras
		boost::shared_ptr<MeshPotato::MPUtils::Camera> buildFrustumCamera(MeshPotato::MPUtils::MPVec3 &eye, openvdb::FloatGrid::Ptr grid) {
			boost::shared_ptr<MeshPotato::MPUtils::Camera> frustumCam = MeshPotato::MPUtils::Camera::Ptr();
			//get bounding box of volume
			openvdb::CoordBBox abbox = grid->evalActiveVoxelBoundingBox();
			if (grid->isInWorldSpace())
				std::cout << "Is in World Space" << std::endl;
			// get center of bounding box of volume
			MeshPotato::MPUtils::MPVec3 abboxcenter = grid->indexToWorld(abbox.getCenter());
			// compute view vector
			MeshPotato::MPUtils::MPVec3 abboxview = (abboxcenter - eye).unit();
			// shoot ray through bounding box to get intersection points
			MeshPotato::MPUtils::MPRay abboxray(eye, abboxview);
			abboxray.worldToIndex(*grid);
			double abboxt0, abboxt1;
			if (abboxray.intersects(abbox, abboxt0, abboxt1))
				std::cout << "good" << std::endl;
			// near point is near plane
			std::cout << "near intersection: " << abboxray(abboxt0)<< std::endl;
			std::cout << "near intersection world: " << grid->indexToWorld(abboxray(abboxt0))<< std::endl;
			double fnearP = (grid->indexToWorld(abboxray(abboxt0)) - eye).dot(abboxview);
			// far point is far plane
			double ffarP = (grid->indexToWorld(abboxray(abboxt1)) - eye).dot(abboxview);

			// Calculate Field of View
			double maxAngle = 0.0;
			double mindistance = 100000000;
			double maxdistance = 0;
			MeshPotato::MPUtils::MPVec3 point1 = grid->indexToWorld(abbox.min());
			MeshPotato::MPUtils::MPVec3 point2 = grid->indexToWorld(openvdb::Coord(abbox.min().x(), abbox.min().y(), abbox.max().z()));
			MeshPotato::MPUtils::MPVec3 point3 = grid->indexToWorld(openvdb::Coord(abbox.min().x(), abbox.max().y(), abbox.min().z()));
			MeshPotato::MPUtils::MPVec3 point4 = grid->indexToWorld(openvdb::Coord(abbox.min().x(), abbox.max().y(), abbox.max().z()));
			MeshPotato::MPUtils::MPVec3 point5 = grid->indexToWorld(openvdb::Coord(abbox.max().x(), abbox.min().y(), abbox.min().z()));
			MeshPotato::MPUtils::MPVec3 point6 = grid->indexToWorld(openvdb::Coord(abbox.max().x(), abbox.min().y(), abbox.max().z()));
			MeshPotato::MPUtils::MPVec3 point7 = grid->indexToWorld(openvdb::Coord(abbox.max().x(), abbox.max().y(), abbox.min().z()));
			MeshPotato::MPUtils::MPVec3 point8 = grid->indexToWorld(abbox.max());
			std::cout << "point1 = " << point1 << std::endl;
			std::cout << "point2 = " << point2 << std::endl;
			std::cout << "point3 = " << point3 << std::endl;
			std::cout << "point4 = " << point4 << std::endl;
			std::cout << "point5 = " << point5 << std::endl;
			std::cout << "point6 = " << point6 << std::endl;
			std::cout << "point7 = " << point7 << std::endl;
			std::cout << "point8 = " << point8 << std::endl;
			std::cout << "Angle = " <<  2*acos((point1 - eye).unit().dot(abboxview))*180/M_PI << std::endl;
			std::cout << "Angle = " <<  2*acos((point2 - eye).unit().dot(abboxview))*180/M_PI << std::endl;
			std::cout << "Angle = " <<  2*acos((point3 - eye).unit().dot(abboxview))*180/M_PI << std::endl;
			std::cout << "Angle = " <<  2*acos((point4 - eye).unit().dot(abboxview))*180/M_PI << std::endl;
			std::cout << "Angle = " <<  2*acos((point5 - eye).unit().dot(abboxview))*180/M_PI << std::endl;
			std::cout << "Angle = " <<  2*acos((point6 - eye).unit().dot(abboxview))*180/M_PI << std::endl;
			std::cout << "Angle = " <<  2*acos((point7 - eye).unit().dot(abboxview))*180/M_PI << std::endl;
			std::cout << "Angle = " <<  2*acos((point8 - eye).unit().dot(abboxview))*180/M_PI << std::endl;
			maxAngle = std::max(maxAngle, 2*acos((point1 - eye).unit().dot(abboxview))*180/M_PI);
			mindistance = std::min(mindistance, (point1 - eye).dot(abboxview));
			maxdistance = max(maxdistance, (point1 - eye).dot(abboxview));
			maxAngle = max(maxAngle, 2*acos((point2 - eye).unit().dot(abboxview))*180/M_PI);
			mindistance = min(mindistance, (point2 - eye).dot(abboxview));
			maxdistance = max(maxdistance, (point2 - eye).dot(abboxview));
			maxAngle = max(maxAngle, 2*acos((point3 - eye).unit().dot(abboxview))*180/M_PI);
			mindistance = min(mindistance, (point3 - eye).dot(abboxview));
			maxdistance = max(maxdistance, (point3 - eye).dot(abboxview));
			maxAngle = max(maxAngle, 2*acos((point4 - eye).unit().dot(abboxview))*180/M_PI);
			mindistance = min(mindistance, (point4 - eye).dot(abboxview));
			maxdistance = max(maxdistance, (point4 - eye).dot(abboxview));
			maxAngle = max(maxAngle, 2*acos((point5 - eye).unit().dot(abboxview))*180/M_PI);
			mindistance = min(mindistance, (point5 - eye).dot(abboxview));
			maxdistance = max(maxdistance, (point5 - eye).dot(abboxview));
			maxAngle = max(maxAngle, 2*acos((point6 - eye).unit().dot(abboxview))*180/M_PI);
			mindistance = min(mindistance, (point6 - eye).dot(abboxview));
			maxdistance = max(maxdistance, (point6 - eye).dot(abboxview));
			maxAngle = max(maxAngle, 2*acos((point7 - eye).unit().dot(abboxview))*180/M_PI);
			mindistance = min(mindistance, (point7 - eye).dot(abboxview));
			maxdistance = max(maxdistance, (point7 - eye).dot(abboxview));
			maxAngle = max(maxAngle, 2*acos((point8 - eye).unit().dot(abboxview))*180/M_PI);
			mindistance = min(mindistance, (point8 - eye).dot(abboxview));
			maxdistance = max(maxdistance, (point8 - eye).dot(abboxview));
			maxAngle += 20;
			if (maxAngle > 90) {
				std::cout<< "WARNING: Light is too close and may not illuminate the entire density!" << std::endl;
			}
			maxAngle = min(89.9999, maxAngle);
			fnearP = mindistance;
			ffarP = maxdistance + maxdistance;
			std::cout << "Frustum Specs:" << std::endl;
			std::cout << "BBOX:" << grid->indexToWorld(abbox.min()) << " " << grid->indexToWorld(abbox.max())<<std::endl;
			std::cout << "Center = " << abboxcenter << std::endl;
			std::cout << "View = " << abboxview << std::endl;
			std::cout << "Ray = " << abboxray << std::endl;
			std::cout << "fnearP = " << fnearP << std::endl;
			std::cout << "ffarP = " << ffarP << std::endl;
			std::cout << "fov = " << maxAngle << std::endl;

			// Computing Up Vector
			MPVec3 up, c;
			if (abboxview.y() != 0 || abboxview.z() != 0)
				c = MPVec3(1,0,0);
			else
				c = MPVec3(0,1,0);
			up = abboxview.cross(c);
			frustumCam->setEyeViewUp(eye, abboxview, up);
			frustumCam->setNearPlane(floorf(fnearP));
			frustumCam->setFarPlane(ceil(ffarP));
			frustumCam->setAspectRatio(1.0);
			frustumCam->setFov(maxAngle);

			return frustumCam;


		}
		
		double computeFOVDegrees(MeshPotato::MPUtils::MPVec3 &point, MeshPotato::MPUtils::MPVec3 &eye, MeshPotato::MPUtils::MPVec3 &view) {
			return 2*acos((point - eye).unit().dot(view))*180/M_PI;
		}
		double computeDistance(MeshPotato::MPUtils::MPVec3 &point, MeshPotato::MPUtils::MPVec3 &eye, MeshPotato::MPUtils::MPVec3 &view) {
			return (point - eye).dot(view);
		}
		/*
		//! Start from the near plane of the frustum grid.  Calculate a ray to the far plane for each cell of the frustum
		void dsm(openvdb::tools::PerspectiveCamera &vdbcam, FrustumGrid *grid, VolumeFloatPtr f) {
		// Get dimensions of the frustum grid by getting it's axis-aligned bounding box
		openvdb::CoordBBox bbox = grid->getBoundingBox();

		int xSize = bbox.max().x() - bbox.min.x();
		int ySize = bbox.max().y() - bbox.min.y();
		int zSize = bbox.max().z() - bbox.min.z();
		for (int j = 0; j < ySize; ++j) {
		for (int i = 0; i < xSize; ++i) {
		float x = (float)i/(xSize - 1);
		float y = (float)j/(ySize - 1);
		MeshPotato::MPUtils::Ray ray = vdbcam->getRay(i,j);
		float deltaS; // (farPlane - nearPlane)/(cam->view*d))/(zSize - 1)

		for (int k = 0; k < zSize; ++k) {
		float val = f->eval(X);
		if (val > 0) {
		value += val * deltaS;
		}
		grid->set(ijk, value);
		}
		}

		}

		}
		 */
	}
}
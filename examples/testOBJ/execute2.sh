#!/bin/sh
g++ readingAndWriting.C -I ../../include -I ../../plugins/VDBOutput/ -I $HOME/projects/alembic/include -I /home/kcoley/Downloads/Alembic_150/Alembic_1.5.0_2013072300/lib -I /home/kcoley/projects/usr/local/include/OpenEXR -L ../../lib -lmeshpotato -L ../../../OpenVDB/lib -L$HOME/projects/alembic/lib -L/home/kcoley/projects/alembic/lib/Alembic/Abc/ -L/home/kcoley/projects/alembic/lib/Alembic/AbcGeom -L/home/kcoley/projects/alembic/lib/Alembic/AbcCoreHDF5 -L/home/kcoley/projects/alembic/lib/Alembic/AbcCollection -L/home/kcoley/projects/alembic/lib/Alembic/AbcMaterial -L/home/kcoley/projects/alembic/lib/AbcOpenGL -L/home/kcoley/projects/alembic/lib/Alembic/AbcCoreAbstract -L/home/kcoley/projects/alembic/lib/Alembic/Util -lopenvdb -lboost_system -lboost_filesystem -L/usr/local/hdf5-1.8.5-patch1/lib -lAlembicAbc -lAlembicAbcGeom -lAlembicAbcCoreHDF5 -lAlembicAbcCollection -lAlembicAbcMaterial -lAlembicAbcOpenGL -lImath -lIex -lboost_thread -lhdf5_hl -lhdf5 -lpthread -lz -lAlembicAbcCoreAbstract -lAlembicUtil -lHalf -o readingAndWriting -ldl
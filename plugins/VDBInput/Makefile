CC=g++
CFLAGS=-c -Wall -fPIC
VDBINCLUDE= /group/dpa/local/include
VDBLIB= /group/dpa/local/openvdb/lib
INCLUDES= -I ../../include -I $(VDBINCLUDE)
LINKS= -L$(VDBLIB) -lopenvdb 
PLUGINFILES=$(*.C)
PLUGINNAME=libVDBInputPlugin.so


BOOST_INC = /usr/include
BOOST_LIB = /usr/lib
PYVDBMESH=pyVDBInputPlugin
OBJECTS=$(PLUGINFILES:.C=.o)
PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)


all: $(PLUGINFILES)
	$(CC) $(CFLAGS) $(INCLUDES) VDBInputPlugin.C -o mpvdbinputplugin.o
	$(CC) -shared -Wl,-soname,$(PLUGINNAME) -o $(PLUGINNAME) mpvdbinputplugin.o $(LINKS)

python: $(PYVDBMESH).C
	$(CC) $(CFLAGS) -I $(PYTHON_INCLUDE) $(PYVDBMESH).C -o $(PYVDBMESH).o
	$(CC) -shared -Wl,-soname,$(PYVDBMESH).so $(PYVDBMESH).o -lpython2.7 -lboost_python -lboost_thread -lboost_system -lboost_filesystem -L./lib -L/group/dpa/local/openvdb/lib -L$(HOME)/projects/MeshPotato/lib -lmeshpotato -lopenvdb /group/dpa/local/openvdb/python/lib/python2.7/pyopenvdb.so -lboost_system -o $(PYVDBMESH).so
	cp $(PYVDBMESH).so ../../pymeshpotato/

clean:
	rm *.o
	rm *.so

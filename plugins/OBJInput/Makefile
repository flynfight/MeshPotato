CC=g++
CFLAGS=-c -Wall -fPIC

INCLUDES= -I ./include -I $(VDBINCLUDE)
LINKS= -L$(VDBLIB) -lopenvdb 
PLUGINFILES=$(*.C)
PLUGINNAME=libOBJInputPlugin.so

BOOST_INC = /usr/include
BOOST_LIB = /usr/lib
PYOBJMESH=pyOBJInputPlugin
OBJECTS=$(PLUGINFILES:.C=.o)
PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)


all: $(PLUGINFILES)
	$(CC) -fPIC -c -I ../../include OBJInputPlugin.C -o mpobjinputplugin.o
	$(CC) -shared -Wl,-soname,$(PLUGINNAME) -o $(PLUGINNAME) mpobjinputplugin.o

python: $(PYOBJMESH).C
	$(CC) $(CFLAGS) -I $(PYTHON_INCLUDE) $(PYOBJMESH).C -o $(PYOBJMESH).o
	$(CC) -shared -Wl,-soname,$(PYOBJMESH).so $(PYOBJMESH).o -lpython2.7 -lboost_python -lboost_thread -lboost_system -lboost_filesystem -L./lib -L/group/dpa/local/openvdb/lib -L$(MESHPOTATO_DIR)/lib -lmeshpotato -lopenvdb /group/dpa/local/openvdb/python/lib/python2.7/pyopenvdb.so -lboost_system -o $(PYOBJMESH).so
	cp $(PYOBJMESH).so ../../pymeshpotato/

clean:
	rm *.o
	rm *.so

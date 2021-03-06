ifeq ("$(shell whoami)", "kcoley")
  CXX = g++
else
  CXX = g++
endif

CC = $(CXX)
C  = cpp

# Warnings frequently signal eventual errors:
#CXXFLAGS  = `sdl-config --cflags` -g -Wall -Weffc++ -Wextra -O2
CXXFLAGS = -g -Wall
ifeq ("$(shell uname)", "Darwin")
  LDFLAGS = -L/opt/local/lib -framework Foundation -framework GLUT -framework OpenGL -lGLEW -lm -L/group/dpa/lib -lOpenImageIO
  CFLAGS  = -I/opt/local/include -I/group/dpa/include -g -std=c++0x
else
  ifeq ("$(shell uname)", "Linux")
  LDFLAGS =  -lm -lX11 -lGL -lGLU -lglut -lGLEW -L/group/dpa/lib -lOpenImageIO -lboost_filesystem -L$(MESHPOTATO_DIR)/lib -lmeshpotato -L/group/dpa/local/openvdb/lib -lopenvdb -lboost_system -lboost_filesystem
  CFLAGS  = -I/group/dpa/include -g -I $(MESHPOTATO_DIR)/include  
#  CFLAGS  = -I/group/dpa/include -g -std=c++0x -I $(MESHPOTATO_DIR)/include
  endif
endif

HFILES 	= MeshViewer.h Camera.h Face.h Vertex.h Material.h Matrix.h Vector.h Utility.h 
OFILES 	= Camera.o Matrix.o Vector.o Utility.o

PROJECT = MeshViewer
EXEC    = meshviewer

$(PROJECT): $(PROJECT).o $(OFILES)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(PROJECT).o $(OFILES) $(LDFLAGS)
	cp $(EXEC) ../bin
$(PROJECT).o: $(PROJECT).$(C) $(HFILES)
	$(CC) $(CFLAGS) -c $(PROJECT).$(C)

Camera.o: Camera.$(C) Camera.h Matrix.h Vector.h Utility.h 
	$(CC) $(CFLAGS) -c Camera.$(C)

Matrix.o: Matrix.$(C) Matrix.h Vector.h Utility.h 
	$(CC) $(CFLAGS) -c Matrix.$(C)

Vector.o: Vector.$(C) Vector.h Utility.h 
	$(CC) $(CFLAGS) -c Vector.$(C)

Utility.o: Utility.$(C) Utility.h
	$(CC) $(CFLAGS) -c Utility.$(C)

clean:
	rm -rf *.o
	rm -rf $(EXEC)
	rm -rf *~

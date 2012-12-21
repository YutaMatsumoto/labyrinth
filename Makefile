
# Compiler and its Options
CC=g++
CXXFLAGS= -g -Wall -std=c++0x # -fpermissive

# Bullet Physics Engine
BSROOT=bullet
BS=./bullet/src
BSD=$(BS)/BulletDynamics/libBulletDynamics.a 
BSC=$(BS)/BulletCollision/libBulletCollision.a 
BSL=$(BS)/LinearMath/libLinearMath.a 
BSS=$(BS)/BulletSoftBody/libBulletSoftBody.a

# Assimp
LIBDIRASSIMP=assimp/lib/

# libs
# LPATH=-Wl,-rpath=lib # embed dynamic library (in ./lib) references into executable
LIBS= -lglut -lGLEW -lGL -lGLU -lassimp $(BSD) $(BSC) $(BSL) $(BSS)
LIBDIR = -L$(LIBDIRASSIMP)

# Mesh Objects
BALL=obj/ball.obj
BOARD=obj/board.obj
MeshAll=$(BALL) $(BORAD)

# Shaders
VSHADER=src/shader.vert
FSHADER=src/shader.frag

# Include Headers
INCLUDEDIR= -I./assimp/ -Ibullet/src -I./assimp/include/assimp # -Ibullet/src/BulletCollision/CollisionShapes/


INITSCRIPT =bin/init.sh

run : bin/j7.out $(BSD) $(BSC) $(BSL) $(BSS)
	. $(INITSCRIPT) && ./$< $(BALL) $(BOARD) $(VSHADER) $(FSHADER)

bin/j7.out : src/j7.cpp 
	$(CC) $(LPATH) $(LIBDIR) $(INCLUDEDIR) $(CXXFLAGS) $< $(LIBS) -o $@
	# $(CC) $(LPATH) $(LIBDIR) $(INCLUDEDIR) $(CXXFLAGS) $< $(LIBS) -o $@  && . ./init.sh && ./$@ $(BALL) $(BOARD)

quick : j6.cpp
	$(CC) $(LPATH) $(LIBDIR) $(INCLUDEDIR) $(CXXFLAGS) j6.cpp $(LIBS) -o j6.out  && . ./init.sh && ./j6.out

j6.out: j6.cpp libbullet libassimp
	$(CC) $(LPATH) $(LIBDIR) $(INCLUDEDIR) $(CXXFLAGS) j6.cpp $(LIBS) -o j6.out  && . ./init.sh && ./j6.out

bullethello.out: bullethello.cpp 
	g++ $(LPATH) $(LIBDIR) $(INCLUDEDIR) $(CXXFLAGS) bullethello.cpp $(LIBS) -o bullethello.out  && ./bullethello.out

# Bullet Library Compilation
$(BSD) $(BSC) $(BSL) $(BSS) :
	cd $(BSROOT) ; cmake . -G "Unix Makefiles" && make ; cd ..

.PHONY : libbullet
libbullet : bullet/Makefile
	cd bullet && make && cd .. && echo "bullet lib done" ; \

libbullet/Makefile : bullet/Makefile
	cd bullet && cmake . -G "Unix Makefiles" && cd ..

.PHONY : assimp
libassimp : assimp/Makefile
	cd assimp && make && cd ..

assimp/Makefile : assimp/CMakeLists.txt
	cd assimp && cmake -G 'Unix Makefiles' 


# $(LIBS) 
# $(INCLUDEDIR) 
j5.out: j5.cpp
	$(CC) $(LPATH) $(LIBDIR) $(CXXFLAGS) j5.cpp $(LIBS) -o j5.out  && ./j5.out

assimp1: assimp-jikken.cpp 
	$(CC) -lassimp $(LPATH) $(LIBDIR) $(CXXFLAGS) assimp-jikken.cpp -o assimp-jikken.out && ./assimp-jikken.out

j4.out: j4.cpp glmdraw.o readtex.o shaderutil.o trackball.o skybox.o glm.o
	$(CC) $(CXXFLAGS) j4.cpp glm.o	glmdraw.o readtex.o shaderutil.o trackball.o skybox.o -o j4.out $(LIBS) && ./j4.out

j3.out: j3.cpp glmdraw.o readtex.o shaderutil.o trackball.o skybox.o glm.o
	$(CC) $(CXXFLAGS) j3.cpp glm.o	glmdraw.o readtex.o shaderutil.o trackball.o skybox.o -o j3.out $(LIBS) && ./j3.out

j2.out: j2.cpp glm2.o glmdraw2.o readtex.o shaderutil.o
	$(CC) $(CXXFLAGS) j2.cpp glm2.o	glmdraw2.o readtex.o shaderutil.o -o j2.out $(LIBS) && ./j2.out

j1.out: j1.cpp
	$(CC) $(CXXFLAGS) j1.cpp -o j1.out $(LIBS) && ./j1.out

glm.o: glm.c
	$(CC) $(CXXFLAGS) -c glm.c

glm2.o: glm2.c
	$(CC) $(CXXFLAGS) -c glm2.c

glmdraw2.o: glmdraw2.c
	$(CC) $(CXXFLAGS) -c glmdraw2.c

glmdraw.o: glmdraw.c
	$(CC) $(CXXFLAGS) -c glmdraw.c

readtex.o: readtex.c
	$(CC) $(CXXFLAGS) -c readtex.c

shaderutil.o: shaderutil.c
	$(CC) $(CXXFLAGS) -c shaderutil.c 

trackball.o: trackball.c trackball.h
	$(CC) $(CXXFLAGS) -c trackball.c 

skybox.o:
	$(CC) $(CXXFLAGS) -c skybox.c

clean: 
	rm *.out *.o bin/j7.out && cd bullet/ && make clean && cd .. 

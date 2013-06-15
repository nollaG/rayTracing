OBJS=GVector3.o main.o Ray.o GObject.o GSphere.o GFlat.o LightSource.o\
	 DirectionalLight.o PointLight.o GComplexModel.o
LDFLAGS=-lm -lGLU -lglut -lpthread
HEADERS=inc/GVector3.h
DEFINES=
CXX=clang++
CFLAGS=-ggdb -O2 -Wall

all:rayTracing
rayTracing:$(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o rayTracing
main.o:inc/GVector3.h main.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o main.o -c main.cc
GVector3.o:inc/GVector3.h GVector3.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o GVector3.o -c GVector3.cc
Ray.o:inc/Ray.h Ray.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o Ray.o -c Ray.cc
GObject.o:inc/GObject.h GObject.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o GObject.o -c GObject.cc
LightSource.o:inc/LightSource.h LightSource.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o LightSource.o -c LightSource.cc
DirectionalLight.o:inc/DirectionalLight.h DirectionalLight.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o DirectionalLight.o -c DirectionalLight.cc
PointLight.o:inc/PointLight.h PointLight.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o PointLight.o -c PointLight.cc
GSphere.o:inc/GSphere.h GSphere.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o GSphere.o -c GSphere.cc
GFlat.o:inc/GFlat.h GFlat.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o GFlat.o -c GFlat.cc
GComplexModel.o:inc/GComplexModel.h GComplexModel.cc
	$(CXX) $(CFLAGS) $(DEFINES) -o GComplexModel.o -c GComplexModel.cc
.PHONY:clean
clean:
	rm rayTracing $(OBJS)

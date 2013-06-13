OBJS=GVector3.o main.o Ray.o GObject.o GSphere.o
LDFLAGS=-lm -lGLU -lglut
HEADERS=inc/GVector3.h
CXX=clang++
CFLAGS=-ggdb -O2

all:rayTracing
rayTracing:$(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o rayTracing
main.o:inc/GVector3.h main.cc
	$(CXX) $(CFLAGS) -o main.o -c main.cc
GVector3.o:inc/GVector3.h GVector3.cc
	$(CXX) $(CFLAGS) -o GVector3.o -c GVector3.cc
Ray.o:inc/Ray.h Ray.cc
	$(CXX) $(CFLAGS) -o Ray.o -c Ray.cc
GObject.o:inc/GObject.h GObject.cc
	$(CXX) $(CFLAGS) -o GObject.o -c GObject.cc
GSphere.o:inc/GSphere.h GSphere.cc
	$(CXX) $(CFLAGS) -o GSphere.o -c GSphere.cc
.PHONY:clean
clean:
	rm rayTracing $(OBJS)

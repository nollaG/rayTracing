OBJS=GVector3.o main.o Ray.o
HEADERS=inc/GVector3.h
CXX=clang++
CFLAGS=-ggdb -O2

all:rayTracing
rayTracing:$(OBJS)
	$(CXX) $(CFLAGS) -o rayTracing $(OBJS)
main.o:inc/GVector3.h main.cc
	$(CXX) $(CFLAGS) -o main.o -c main.cc
GVector3.o:inc/GVector3.h GVector3.cc
	$(CXX) $(CFLAGS) -o GVector3.o -c GVector3.cc
Ray.o:inc/Ray.h Ray.cc
	$(CXX) $(CFLAGS) -o Ray.o -c Ray.cc
.PHONY:clean
clean:
	rm rayTracing $(OBJS)

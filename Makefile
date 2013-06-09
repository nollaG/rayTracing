OBJS=GVector3.o main.o
HEADERS=inc/GVector3.h
CXX=clang++
CFLAGS=-ggdb -O2

all:rayTracing
rayTracing:$(OBJS)
	$(CXX) $(CFLAGS) -o rayTracing $(OBJS)
main.o:inc/GVector3.h
GVector3.o:inc/GVector3.h
.PHONY:clean
clean:
	rm rayTracing $(OBJS)

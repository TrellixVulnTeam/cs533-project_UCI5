CPP_FLAGS =-Wall -g -O3
LD_FLAGS =-lpthread
all: cacheline.o sim.o
	g++ $^ -o sim $(LD_FLAGS) $(CPP_FLAGS)

cacheline.o: cacheline.cpp
	g++  $(CPP_FLAGS) $^ -c

sim.o: sim.cpp
	g++ -c $(CPP_FLAGS) $^ -c

clean: 
	rm -f *.o sim


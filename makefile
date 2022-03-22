all: liebs

liebs: lieberman_j_p2.o minHeap.o
	g++ lieberman_j_p2.o minHeap.o -g -o program2

liebs.o: lieberman_j_p2.cpp
	g++ -g -c lieberman_j_p2.cpp

minHeap.o: minHeap.cpp minHeap.h
	g++ -g -c minHeap.cpp

clean:
	rm -f *.o program1
all: project1b.out

project1b.out: project1b.cpp hash24.cpp hash24.h dictionary.cpp dictionary.h 
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out


all: project1b.out

project1b.out: project1b.cpp hash24.cpp dictionary.cpp 
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out


all: project1b.out

project1b.out: project1b.cpp hash24.cpp dictionary.cpp 
	g++  $^ -o $@

clean:
	rm -f *.out


all: compile run

compile:
		g++ -I ./include/ -o ./lib/DNA.o -c ./src/DNA.cpp
		g++ -I ./include/ -o ./bin/program ./lib/DNA.o ./src/main.cpp
run:
	./bin/program

all: prog1

prog1: main.cpp graph.cpp
		g++ -g graph.cpp main.cpp -o prog1.out

clean:
		rm prog1.out
Main: Main.cpp
	g++ -g -Wall -std=c++11 -fopenmp -o Main Main.cpp
	
Neuron.o: Neuron.hpp
	g++ -g -Wall -std=c++11 -o Neuron.hpp
	
Brain.o: Brain.hpp
	g++ -g -Wall -std=c++11 -o Brain.hpp
	
clean:
	-rm Main
	
run:
	make clean
	make Main
	clear
	./Main
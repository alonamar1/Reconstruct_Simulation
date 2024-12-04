# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
# All Targets
all: clean link run checkMemo

link: compile
	@echo "Linking object files"
	g++ -o bin/main bin/Checks.o bin/main.o bin/Settlement.o bin/Auxiliary.o bin/Facility.o bin/SelectionPolicy.o bin/Plan.o bin/Simulation.o bin/Action.o

compile: src/main.cpp src/Auxiliary.cpp
	@echo "Compiling source code"
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Settlement.o src/Settlement.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/main.o src/main.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Facility.o src/Facility.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Plan.o src/Plan.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Simulation.o src/Simulation.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Action.o src/Action.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Checks.o src/Checks.cpp
run:
	@echo "Run Program"
	./bin/main config_file.txt

clean:
	@echo "Cleaning bin directory"
	rm -f bin/*
checkMemo:
	valgrind --leak-check=full --show-reachable=yes ./bin/main ./config_file.txt
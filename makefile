# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
# All Targets
all: clean link run

link: compile
	@echo "Linking object files"
	g++ -o bin/main bin/main.o bin/Settlement.o bin/Auxiliary.o bin/Facility.o

compile: src/main.cpp src/Auxiliary.cpp
	@echo "Compiling source code"
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Settlement.o src/Settlement.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/main.o src/main.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Auxiliary.o src/Auxiliary.cpp
	g++ -g -I "include/" -c -Wall -Weffc++ -std=c++11 -o bin/Facility.o src/Facility.cpp
run:
	./bin/main config_file.txt

clean:
	@echo "Cleaning bin directory"
	rm -f bin/*
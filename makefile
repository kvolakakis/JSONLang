compile:
	g++ JSONLang.cpp  -std=c++0x -o json

execute:
	./json

all:
	g++ JSONLang.cpp  -std=c++0x -o json
	./json

clean:
	rm *.exe *.out

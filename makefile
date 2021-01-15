compile:
	g++ JSONLang.cpp -o json

execute:
	./json

all:
	g++ JSONLang.cpp -o json
	./json

clean:
	rm *.exe *.out

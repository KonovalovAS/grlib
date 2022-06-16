all:  prog

prog: o/main.o o/canvas.o
	g++ o/main.o o/canvas.o -o prog

o/main.o: main.cpp
	g++ -c main.cpp
	mv main.o o

o/canvas.o: src/canvas.cpp
	g++ -c src/canvas.cpp
	mv canvas.o o

clean:
	rm o/*.o


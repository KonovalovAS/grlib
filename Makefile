all:  prog

prog: o/main.o o/grobj.o o/canvas.o o/color.o o/pov.o
	g++ o/main.o o/grobj.o o/canvas.o o/color.o o/pov.o -o prog

o/main.o: main.cpp
	g++ -c main.cpp
	mv main.o o

o/grobj.o: src/grobj.cpp
	g++ -c src/grobj.cpp
	mv grobj.o o

o/canvas.o: src/canvas.cpp
	g++ -c src/canvas.cpp
	mv canvas.o o

o/color.o: src/color.cpp
	g++ -c src/color.cpp
	mv color.o o

o/pov.o: src/pov.cpp
	g++ -c src/pov.cpp
	mv pov.o o

clean:
	rm o/*.o


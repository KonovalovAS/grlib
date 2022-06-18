o = o_files

objects_list = main.o grobj.o canvas.o color.o pov.o
objects = $(addprefix $(o)/,$(objects_list))

all:  prog

prog: $(objects) 
	g++ $(objects) -o prog

$(o)/main.o: main.cpp
	g++ -o $(o)/main.o -c main.cpp

$(o)/grobj.o: src/grobj.cpp
	g++ -o $(o)/grobj.o -c src/grobj.cpp

$(o)/canvas.o: src/canvas.cpp
	g++ -o $(o)/canvas.o -c src/canvas.cpp

$(o)/color.o: src/color.cpp
	g++ -o $(o)/color.o -c src/color.cpp

$(o)/pov.o: src/pov.cpp
	g++ -o $(o)/pov.o -c src/pov.cpp 

clean:
	rm o/*.o


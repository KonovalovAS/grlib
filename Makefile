o = o_files
src = src

objects_list = main.o grobj.o canvas.o color.o pov.o noise_eliminator.o converter.o writer.o
objects = $(addprefix $(o)/,$(objects_list))

all:  prog

prog: $(objects) 
	g++ $(objects) -o prog

$(o)/main.o: main.cpp
	g++ -o $(o)/main.o -c main.cpp

$(o)/grobj.o: $(src)/grobj.cpp
	g++ -o $(o)/grobj.o -c $(src)/grobj.cpp

$(o)/canvas.o: $(src)/canvas.cpp
	g++ -o $(o)/canvas.o -c $(src)/canvas.cpp

$(o)/color.o: $(src)/color.cpp
	g++ -o $(o)/color.o -c $(src)/color.cpp

$(o)/pov.o: $(src)/pov.cpp
	g++ -o $(o)/pov.o -c $(src)/pov.cpp 

$(o)/noise_eliminator.o: $(src)/noise_eliminator.cpp
	g++ -o $(o)/noise_eliminator.o -c $(src)/noise_eliminator.cpp

$(o)/converter.o: $(src)/converter.cpp
	g++ -o $(o)/converter.o -c $(src)/converter.cpp

$(o)/writer.o: $(src)/writer.cpp
	g++ -o $(o)/writer.o -c $(src)/writer.cpp

clean:
	rm $(o)/*.o


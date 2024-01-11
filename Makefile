CC := clang++

project_output := ga.o 

$(project_output): clean  
	@echo "Compiling files...."
	$(CC) *.cpp */*.cpp -o $(project_output) -lSDL2main -lSDL2

.PHONY : clean config_sdl
clean:
	@echo "Cleaning files..."
	rm -rf *.out

config_sdl: 
	pkg-config --libs --cflags sdl2

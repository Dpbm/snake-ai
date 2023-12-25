CC := clang++

compile: clean
	@echo "Compiling files...."
	${CC} *.cpp -o ga.out -lSDL2main -lSDL2

.PHONY : clean config_sdl
clean:
	@echo "Cleaning files..."
	rm -rf *.out

config_sdl: 
	pkg-config --libs --cflags sdl2

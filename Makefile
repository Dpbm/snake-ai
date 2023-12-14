CC := clang++

default: clean compile

clean:
	@echo "Cleaning files..."
	rm -rf *.out

compile:
	@echo "Compiling files...."
	${CC} *.cpp -o ga.out

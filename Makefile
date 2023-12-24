CC := clang++

compile: clean
	@echo "Compiling files...."
	${CC} *.cpp -o ga.out

.PHONY : clean
clean:
	@echo "Cleaning files..."
	rm -rf *.out

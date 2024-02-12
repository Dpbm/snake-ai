# Snake game genetic algorithm

![Build-Test workflow (cmake)](https://github.com/Dpbm/genetic-algorithm/actions/workflows/cmake-build-test.yml/badge.svg)

*🚧In Progress🚧*

The idea for this project came as a joint between my urge to learn `C++` and to implement a `AI` from scratch.\
So, actually, this project is a big lab for me, the main goal is to learn things like:

* c++
* cmake/make
* ctest
* AI algorithms
* docker
* SDL2

Bellow there're some youtube videos that have inspired me to create this project:


[![Artificial Intelligence in Google's Dinosaur (English Sub)](https://img.youtube.com/vi/P7XHzqZjXQs/0.jpg)](https://youtu.be/P7XHzqZjXQs)
[![Rede Neural aprendendo a jogar o jogo da cobrinha (SNAKE)
](https://img.youtube.com/vi/awz1ghokP3k/0.jpg)](https://youtu.be/awz1ghokP3k)
[![MarI/O - Machine Learning for Video Games](https://img.youtube.com/vi/qv6UVOQ0F44/0.jpg)](https://youtu.be/qv6UVOQ0F44)


## Technologies

Here are listed the technologies used for this project:

* [git](https://git-scm.com/)
* [SDL2](https://www.libsdl.org/)
* [C++](https://isocpp.org/)
* [make](https://www.gnu.org/software/make/)/[cmake](https://cmake.org/)
* [googletest (ctest)](https://google.github.io/googletest/)
* [sh](https://www.gnu.org/software/bash/)
* [Github actions](https://docs.github.com/en/actions)


## Dev usage

to build the and run the project you must have a `linux distro` and the following tools and libraries installed:

* [git](https://git-scm.com/)
* [SDL2](https://www.libsdl.org/)
* [C++](https://isocpp.org/)
* [make](https://www.gnu.org/software/make/)
* [cmake](https://cmake.org/)
* [sh](https://www.gnu.org/software/bash/)

with all that seted up, clone the project, go to thedirectory and run the `compilation script` as:

```bash
git clone https://github.com/Dpbm/genetic-algorithm
cd ./genetic-algorithm
chmod +x ./compile.sh ./clean.sh
./clean.sh && ./compile.sh main.cpp
```

then, to run the project type:
```bash
./build/ga.out
```

and to run the tests:

```bash
cd build
ctest
```

## Project Structure

The project implements all from scratch, and the sub-libraries are organized in the following structure:

1. [game](./game): This folder contains all the implementation of the snake game itself, 
SDL abstractions, etc.

2. [genetic](./genetic): The genetic algorithm utils, like genes and chromossomes code.

3. [matrix](./matrix): The sub-library to handle matrices in a simple way.

4. [helpers](./helpers): Some uility functions, like random.

5. [machine](./machine): Parts to build a Neural Network. 

Then all this is embedded into the [main.cpp](./main.cpp) file, to build the project altogether.


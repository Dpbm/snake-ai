# Snake AI




https://github.com/Dpbm/snake-ai/assets/75098594/81120c76-1979-4c08-8647-6a0fb24e64d4




![Build-Test workflow (cmake)](https://github.com/Dpbm/snake-ai/actions/workflows/cmake-build-test.yml/badge.svg)
![Docker Hub publish](https://github.com/Dpbm/snake-ai/actions/workflows/dockerhub.yml/badge.svg)
![GHRC publish](https://github.com/Dpbm/snake-ai/actions/workflows/ghrc.yml/badge.svg)

For this project, my idea was to explore some algorithms, such as genetic algorithms and Qubo, and 
technologies, like C++, to develop something I've always wanted to, all from scratch! 

The urge to build a snake game AI came after I watched some YouTube videos, which inspired me to create something different and just for fun, some of them are listed bellow:

[![Artificial Intelligence in Google's Dinosaur (English Sub)](https://img.youtube.com/vi/P7XHzqZjXQs/0.jpg)](https://youtu.be/P7XHzqZjXQs)
[![Rede Neural aprendendo a jogar o jogo da cobrinha (SNAKE)
](https://img.youtube.com/vi/awz1ghokP3k/0.jpg)](https://youtu.be/awz1ghokP3k)
[![MarI/O - Machine Learning for Video Games](https://img.youtube.com/vi/qv6UVOQ0F44/0.jpg)](https://youtu.be/qv6UVOQ0F44)


## Technologies

The Technologies used were:

* [git](https://git-scm.com/)
* [SDL2](https://www.libsdl.org/)
* [C++](https://isocpp.org/)
* [make](https://www.gnu.org/software/make/)/[cmake](https://cmake.org/)
* [googletest (ctest)](https://google.github.io/googletest/)
* [sh](https://www.gnu.org/software/bash/)
* [Github actions](https://docs.github.com/en/actions)
* [python 3.10](https://www.python.org/) (used to test the QUBO model)
* [pygame](https://www.pygame.org/)
* [docker](https://www.docker.com/)
* [docker compose](https://docs.docker.com/compose/)


## Different modes

In this version of snake game, I've implemented 3 game modes:

### Play as human

As the classic one, your can play and enjoy the game by yourself, without any machine inteligent agent.

`PRESS D` to start playing and use the `WASD` to move the snake around.



https://github.com/Dpbm/snake-ai/assets/75098594/c66b2d44-d027-446a-ba97-bae4b6e7269e



### AI

In the AI version, you have 2 screens to select either train the AI or let the AI play.

#### Train AI
To train the AI `PRESS A` and let her learn to play. If you want you can `PRESS S` during the training to save the best individual weights, but after each generation a weights file is save with the best one. If you want to go back from the training module, you can also `PRESS R` to return to the main Screen.



https://github.com/Dpbm/snake-ai/assets/75098594/71f9e79c-d6b0-4472-a7f9-cab7c918636b



#### Let the AI play

After acquaring the weights file (`.wg`), you can put them into an AI agent to play. To do that, just `PRESS S` at the main SCreen, and import your `.wg` file.


### QUBO

The last mode, is based on QUBO model. This one has a mathematical an expression with some binary variables, and the goal is to minimize it using different combinations for these binary variables.

$$\sum_{i = 0}^{2}{Q_{ii}x_{i}} + P((\sum_{i = 0}^{2}{x_{i}})-1)^2$$

In this expression, $Q$ is a matrix with the distances between the player and the food, which:

```
Q[0][0] = distance if the player go foward (in the same direction he was)
Q[1][1] = distance if the player go down/right 
Q[2][2] = distance if the player go up/left

anything else are just zeros
```

$x_i$ is the binary variable $i$. $P$ is a penality value, in this case we used $(window_{height}*window_{width}) + 10$, the penality part ensures that only one movement will be passed as outcome (either $001$, $010$ or $100$).

To play this one, `PRESS Q` at the start Screen.



https://github.com/Dpbm/snake-ai/assets/75098594/341a7d76-11cf-4371-9a8f-ba7a36f9fcd3



## Usage

All the following usage ways are focused on `Ubuntu` based distros, so some steps may differ for different OS. Remember to check the tools documentation for your system. 

### Docker

The simplest way to run it, is by using Docker. 

First pull the image:
```bash
docker pull dpbm32/snake-ai

# or using the GHRC version
docker pull ghcr.io/dpbm/snake-ai:latest
```

Then you must grant access to your `XDisplay`.

```bash
xhost +local:root

# remeber revoking access after using it
xhost -local:root
```

Also, setup a docker volume for the neural network weights output.

```bash
docker volume create weights-out
```

Finally run the image:

```bash
docker run -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
           -v /path/to/your/weights/input/folder/optional/:/snake/weights_input/ \
           --mount source=weights-out,target=/snake/weights_output/ \
           -e DISPLAY=$DISPLAY \
           -e WPATH=/snake/weights_output/ \
           snake-ai
```

### Docker build local

Another way to do that is build the image by yourself. To do that run:

```bash
docker build -t snake-ai .
```

Then follow the steps after the `docker pull` from the [#docker section](#docker).

### Docker compose

Finally, There's a [compose file](compose.yaml) in the project directory that you can use to orchestrate the image requirements. 

After creating a volume and giving the `XDisplay` permissions, run:

```bash
docker compose up
```

### Dev Build

To build the and run the project, you must the following tools and libraries installed:

* [git](https://git-scm.com/)
* [SDL2](https://www.libsdl.org/)
* [C++](https://isocpp.org/)
* [make](https://www.gnu.org/software/make/)
* [cmake](https://cmake.org/)
* [sh](https://www.gnu.org/software/bash/)

Then, clone the project and run the `compilation script`:

```bash
git clone https://github.com/Dpbm/snake-ai
cd ./snake-ai
chmod +x ./compile.sh ./clean.sh
./clean.sh && ./compile.sh main.cpp
```

Finally, run the game:

```bash
LC_NUMERIC="C" ./build/snake

# or, if you want to set a different path to the output weights
LC_NUMERIC="C" WPATH="/path/to/save/the/weights/" ./build/snake

```


### Tests

In case you want to run the tests by your own, do the following:

```bash
cd build
ctest
```

### Qubo test

Finally, inside this repo, there's a subproject made in python to test the Qubo model and how we could use it to play snake game.
To access this piece of software:

Install the dependencies: 

```bash
pip install -r requirements.txt #use python>=3.10

#or using conda (recommended)
conda env create -f conda-lock.yml
conda activate snake-ai
```

and run:

```bash
python ./pygame-qubo-test/main.py
```



https://github.com/Dpbm/snake-ai/assets/75098594/783bd111-b414-4b62-893c-becf346cb6c8


If you want to understand how the tests to map the qubo version were done, you can do:

```
# case you used pip before
# pip install -r requirements-dev.txt

jupyter lab qubo-test.ipynb
```


## Credits

Fonts were taken from: [CodeMan38 Google fonts](https://fonts.google.com/specimen/Press+Start+2P)\
nativefiledialog-extended by [btzy](https://github.com/btzy/nativefiledialog-extended)

#!/usr/bin/sh

set -e

GREEN="\e[32m"
ENDCOLOR="\e[0m"

chmod +x ./clean.sh
chmod +x ./compile.sh

printf "${GREEN}Cleaning directories...${ENDCOLOR}"
./clean.sh
printf "\n\n"

printf "${GREEN}Compiling: 'manual_tests.cpp'${ENDCOLOR}\n"
./compile.sh manual_tests.cpp
printf "\n\n"

printf "${GREEN}Running: 'manual_tests'${ENDCOLOR}\n"
./build/ga.out
printf "\n\n"

printf "${GREEN}Compiling: 'main.cpp'${ENDCOLOR}\n"
./compile.sh main.cpp
printf "\n\n"


printf "${GREEN}Running tests${ENDCOLOR}\n"
cd build && rm -rf *.wg && ctest -V
printf "\n\n"

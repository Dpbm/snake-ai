#!/usr/bin/sh

set -e

GREEN="\e[32m"
ENDCOLOR="\e[0m"

chmod +x ./clean.sh
chmod +x ./compile.sh
chmod +x ./setup-nfd.sh

printf "${GREEN}Cleaning directories...${ENDCOLOR}"
./clean.sh
printf "\n\n"

printf "${GREEN}Getting NativeFileDialog...${ENDCOLOR}"
./setup-nfd.sh
printf "\n\n"

printf "${GREEN}Compiling: 'manual', 'snake' and 'tests'${ENDCOLOR}\n"
./compile.sh 
printf "\n\n"

printf "${GREEN}Running: 'manual_tests'${ENDCOLOR}\n"
./build/manual
printf "\n\n"

printf "${GREEN}Running tests${ENDCOLOR}\n"
cd build && rm -rf *.wg && ctest -V
printf "\n\n"

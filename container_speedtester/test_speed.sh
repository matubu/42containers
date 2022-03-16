#!/bin/bash

black="[1;30m"
red="[1;32m"
green="[1;32m"
yellow="[1;33m"
blue="[1;36m"
magenta="[1;35m"
cyan="[1;36m"
white="[1;37m"

bg_black="[40m"
bg_red="[41m"
bg_green="[42m"
bg_yellow="[43m"
bg_blue="[44m"
bg_magenta="[45m"
bg_cyan="[46m"
bg_white="[47m"
rc="[0m"

C=clang++
D="-D NAME=ft"
DSTD="-D NAME=std"
sr="vector_capacity_print.cpp"

echo -n "$bg_red STACK $rc"
bash stack_speed.sh
echo -n "$bg_red SET $rc"
bash set_speed.sh
echo -n "$bg_red VECTOR $rc"
bash vector_speed.sh
echo -n "$bg_red MAP $rc"
bash map_speed.sh
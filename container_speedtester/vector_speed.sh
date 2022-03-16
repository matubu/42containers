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
cd vector/capacity
sr="vector_capacity_print.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $T vector_capacity_print.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_capacity_print.cpp -o one && time ./one
sr="vector_reserve.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $sr -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD $sr -o one && time ./one

sr="vector_resize.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_resize.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_resize.cpp -o one && time ./one

cd ../element_access

sr="vector_at.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_at.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_at.cpp -o one && time ./one

sr="vector_back.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_back.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_back.cpp -o one && time ./one

sr="vector_front.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_front.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_front.cpp -o one && time ./one

sr="vector_square_bracket.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_square_bracket.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_square_bracket.cpp -o one && time ./one

cd ../modifier

sr="vector_assign.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_assign.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_assign.cpp -o one && time ./one
sr="vector_clear.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_clear.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_clear.cpp -o one && time ./one

sr="vector_erase.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_erase.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_erase.cpp -o one && time ./one

sr="vector_insert.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_insert.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_insert.cpp -o one && time ./one

sr="vector_pop_back.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_pop_back.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_pop_back.cpp -o one && time ./one

sr="vector_swap.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D vector_swap.cpp -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD vector_swap.cpp -o one && time ./one
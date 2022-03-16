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

cd map
C=clang++
D="-D NAME=ft"
DSTD="-D NAME=std"

cd ./element_access

sr="map_count.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $sr -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD $sr -o one && time ./one

sr="map_find.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $sr -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD $sr -o one && time ./one

sr="map_access.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $sr -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD $sr -o one && time ./one


cd ../modifier

sr="map_clear.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $sr -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD $sr -o one && time ./one

sr="map_insert.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $sr -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD $sr -o one && time ./one

sr="map_erase.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $sr -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD $sr -o one && time ./one

sr="map_swap.cpp"
echo "$blue$sr$rc"
echo -n "$red FT TIME :$rc"
$C $D $sr -o one && time ./one
echo -n "$red STD TIME :$rc"
$C $DSTD $sr -o one && time ./one
 
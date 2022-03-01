#!/bin/bash

INCLUDES="../"

RED="\033[31m"
OK="\xE2\x9C\x85"
RESET="\033[0m"
BOLD="\033[1m"

rm -rf */*_std */*_ft */*dSYM

run_test() {
    echo -en "$BOLD""Test $1 $RESET "
    g++ -Wall -Wextra -Werror -Wno-unused -I $INCLUDES -D STD "$1" -o "$1"_std
	g++ -Wall -Wextra -Werror -Wno-unused -g -I $INCLUDES "$1" -o "$1"_ft
    if [ "$?" -ne 0 ]
    then
        return
    fi
    ./"$1"_std > "$1"_log_std
    ./"$1"_ft > "$1"_log_ft
    if [ $? -ne 0 ]
    then
        return  
    fi 
    if [ $(diff "$1"_log_std "$1"_log_ft | wc -l) -ne 0 ]
    then
        echo -e "$RED""DIFF : ""$RESET"
        diff --suppress-common-lines --old-line-format="STD %5dn< %L" --new-line-format="FT  %5dn> %L" \
            --unchanged-line-format="" "$1"_log_std "$1"_log_ft
        return
    elif [ "$2" == "v" ]
    then
        valgrind ./"$1"_ft > /dev/null 2> leaks
        if [ $(cat leaks | grep -E "definitely|indirectly" | grep "0 bytes in 0 blocks" | wc -l) -ne 2 ]
        then
            cat leaks | grep -E "definitely|indirectly" | grep -v  "0 bytes in 0 blocks"   
            return
        fi
        rm -rf leaks *.dSYM
    fi
    echo -e "$OK" 
}

if [ "$1" == "clean" ]
then
    rm -rf */*_std */*_ft */*dSYM
    exit
fi

MAINS=($(ls "$1"/*.cpp))

for M in "${MAINS[@]}"
do
    run_test $M $2
    rm -rf "$1"/*dSYM
done

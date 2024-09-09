#!/usr/bin/env bash

green=`tput setaf 2`
yellow=`tput setaf 3`
reset=`tput sgr0`

echo "${yellow}compile? [y\n]${reset}"
read compile_var
echo "${yellow}run? [y\n]${reset}"
read run_var
if [ "$run_var" == "y" ]
then
    echo "${yellow}with valgrind? [y\n]${reset}"
    read val_var
fi
echo "${yellow}delete the executable aftewards? [y\n]${reset}"
read del_var

if [ "$compile_var" == "y" ]
then
    rm -f unit_test_exec
    echo "${yellow}compiling${reset}"
    g++ -std=c++11 -g -Wall -Werror -pedantic-errors -ggdb3 -DNDEBUG ./unit_tests/*.cpp ./*.cpp -o unit_test_exec
    echo "${yellow}finish${reset}"
fi

if [ "$run_var" == "y" ]
then
    if [ -e ./unit_test_exec ]
    then
    if [ "$val_var" == "y" ]
    then    
        echo "${yellow}running with valgrind${reset}"
        valgrind --leak-check=full -s ./unit_test_exec
        echo "${yellow}finish${reset}"
    elif [ "$val_var" == "n" ]
    then
        echo "${yellow}running exec${reset}"
        ./unit_test_exec
        echo "${yellow}finish${reset}"
    fi
    else
        echo "${yellow}no executable present - can't run${reset}"
    fi
fi


if [ "$del_var" == "y" ]
then
    if [ -e ./unit_test_exec ]
    then
        rm -f unit_test_exec
        echo "${yellow}unit_test_exec removed${reset}"
    fi
fi

echo "${green}finish running script${reset}"
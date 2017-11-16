#!/bin/bash
#tests multi commands

TEST1="pwd #display directory"
TEST2="ls # -a"
TEST3="ls -a #; pwd"
TEST4="ls -a; pwd # || && ; echo ; sd"
TEST5="echo hello world && FAILCOMMAND how are you doing && echo I'm #doing great"
TEST6="#Just a comment"

echo -e "Test 1: $TEST1"
echo -e $TEST1 | ./bin/rshell
echo -e "\nTest 2: $TEST2"
echo -e $TEST2 | ./bin/rshell
echo -e "\nTest 3: $TEST3"
echo -e $TEST3 | ./bin/rshell
echo -e "\nTest 4: $TEST4"
echo -e $TEST4 | ./bin/rshell
echo -e "\nTest 5: $TEST5"
echo -e $TEST5 | ./bin/rshell
echo -e "\nTest 6: $TEST6"
echo -e $TEST6 | ./bin/rshell

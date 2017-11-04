#!/bin/bash
#tests multi commands

TEST1="pwd #display directory"
TEST2="ls # -a"
TEST3="ls -a #; pwd"
TEST4="ls -a; pwd # || && ; echo ; sd"
TEST5="echo hello world && FAILCOMMAND how are you doing && echo I'm #doing great"
TEST6="#Just a comment"

echo Test 1
echo -e $TEST1 | ./bin/rshell
echo Test 2
echo -e $TEST2 | ./bin/rshell
echo Test 3
echo -e $TEST3 | ./bin/rshell
echo Test 4
echo -e $TEST4 | ./bin/rshell
echo Test 5
echo -e $TEST5 | ./bin/rshell
echo Test 6
echo -e $TEST6 | ./bin/rshell
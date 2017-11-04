#!/bin/bash
#tests multi commands

TEST1="pwd #display directory"
TEST2="ls # -a"
TEST3="ls -a #; pwd"
TEST4="ls -a; pwd # || && ; echo ; sd"
TEST5="echo hello world && FAILCOMMAND how are you doing && echo I'm #doing great"
TEST6="#Just a comment"

echo -e $TEST1 | ./bin/rshell
echo -e $TEST2 | ./bin/rshell
echo -e $TEST3 | ./bin/rshell
echo -e $TEST4 | ./bin/rshell
echo -e $TEST5 | ./bin/rshell
echo -e $TEST6 | ./bin/rshell
#!/bin/bash
#tests single commands

TEST1="ls -a"
TEST2="echo hello"
TEST3="echo hello world"
TEST4="echo hello world ! ! ! !"
TEST5=""
TEST6="pwd"

echo $TEST1 | ./bin/rshell
echo $TEST2 | ./bin/rshell
echo $TEST3 | ./bin/rshell
echo $TEST4 | ./bin/rshell
echo $TEST5 | ./bin/rshell
echo $TEST6 | ./bin/rshell
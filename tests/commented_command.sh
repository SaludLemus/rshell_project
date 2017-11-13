#!/bin/bash
#tests multi commands

TEST1="pwd #display directory"
TEST2="ls # -a"
TEST3="ls -a #; pwd"
TEST4="ls -a; pwd # || && ; echo ; sd"
TEST5="echo hello world && FAILCOMMAND how are you doing && echo I'm #doing great"
TEST6="#Just a comment"
TEST7="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n" | ./bin/rshell
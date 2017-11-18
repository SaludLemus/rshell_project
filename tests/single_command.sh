#!/bin/bash
#tests single commands

TEST1="pwd"
TEST2="ls -a"
TEST3="echo \"||\""
TEST4="echo hello world ! ! ! !"
TEST5="\n"
TEST6="FAILCOMMAND"
TEST7="FAILCOMMAND FAILPARAMETER"
TEST8="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n" | ./bin/rshell


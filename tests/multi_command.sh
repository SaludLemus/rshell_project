#!/bin/bash
#tests multi commands

TEST1="pwd; ls -a"
TEST2="echo hello world; echo how are you doing; echo I'm doing great"
TEST3="echo hello world && echo how are you doing; echo I'm doing great"
TEST4="echo hello world ! ! ! !"
TEST5='\n'
TEST6="pwd"
TEST7="FAILCOMMAND"

echo -e $TEST1 | ./bin/rshell
echo -e $TEST2 | ./bin/rshell
echo -e $TEST3 | ./bin/rshell
echo -e $TEST4 | ./bin/rshell
echo -e $TEST5 | ./bin/rshell
echo -e $TEST6 | ./bin/rshell
echo -e $TEST7 | ./bin/rshell
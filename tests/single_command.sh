#!/bin/bash
#tests single commands

TEST1="pwd"
TEST2="ls -a"
TEST3="echo '||'"
TEST4="echo hello world ! ! ! !"
TEST5="\n"
TEST6="FAILCOMMAND"
TEST7="FAILCOMMAND FAILPARAMETER"

echo -e $TEST1 | ./bin/rshell
echo -e $TEST2 | ./bin/rshell
echo -e $TEST3 | ./bin/rshell
echo -e $TEST4 | ./bin/rshell
echo -e $TEST5 | ./bin/rshell
echo -e $TEST6 | ./bin/rshell
echo -e $TEST7 | ./bin/rshell
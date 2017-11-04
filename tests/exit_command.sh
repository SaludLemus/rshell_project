#!/bin/bash
#tests multi commands

TEST1="exit"
TEST2="ls -a; exit"
TEST3="ls -a && exit"
TEST4="FAILCOMMAND -a || exit"
TEST5="echo "exit""
TEST6="echo sup fam; echo sup back #exit"

echo -e $TEST1 | ./bin/rshell
echo -e $TEST2 | ./bin/rshell
echo -e $TEST3 | ./bin/rshell
echo -e $TEST4 | ./bin/rshell
echo -e $TEST5 | ./bin/rshell
echo -e $TEST6 | ./bin/rshell
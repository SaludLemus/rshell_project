#!/bin/bash
#tests multi commands

TEST1="exit"
TEST2="ls -a; exit"
TEST3="ls -a && exit"
TEST4="FAILCOMMAND -a || exit"
TEST5="echo exit; exit"
TEST6="echo sup fam; echo sup back #exit"
TEST7="exit"

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
echo -e "$TEST6\n$TEST7\n" | ./bin/rshell
#!/bin/bash
#tests single commands

TEST1="pwd"
TEST2="ls -a"
TEST3="echo '||'"
TEST4="echo hello world ! ! ! !"
TEST5="\n"
TEST6="FAILCOMMAND"
TEST7="FAILCOMMAND FAILPARAMETER"

echo -e "Test 1: $TEST1"
echo -e $TEST1 | ./bin/rshell
echo -e "\nTest 2: $TEST2"
echo -e $TEST2 | ./bin/rshell
echo -e "\nTest 3: $TEST3"
echo -e $TEST3 | ./bin/rshell
echo -e "\nTest 4: $TEST4"
echo -e $TEST4 | ./bin/rshell
echo -e "\nTest 5: newline"
echo -e $TEST5 | ./bin/rshell
echo -e "\nTest 6: $TEST6"
echo -e $TEST6 | ./bin/rshell
echo -e "\nTest 7: $TEST7"
echo -e $TEST7 | ./bin/rshell
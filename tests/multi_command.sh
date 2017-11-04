#!/bin/bash
#tests multi commands

TEST1="pwd; ls -a"
TEST2="echo These lines; echo should work; echo without problem"
TEST3="echo hello world && echo how are you doing; echo I'm doing great"
TEST4="echo hello world || echo how are you doing; echo I'm doing great"
TEST5="echo hello world && echo how are you doing && echo I'm doing great"
TEST6="echo hello world && FAILCOMMAND how are you doing && echo I'm doing great"
TEST7="echo hello world || FAILCOMMAND how are you doing && echo I'm doing great"

echo "Test 1: $TEST1"
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
echo -e $TEST6 | ./bin/rshell
echo -e "\nTest 7: $TEST7"
echo -e $TEST7 | ./bin/rshell
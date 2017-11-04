#!/bin/bash
#tests multi commands

TEST1="pwd; ls -a"
TEST2="echo hello world; echo how are you doing; echo I'm doing great"
TEST3="echo hello world && echo how are you doing; echo I'm doing great"
TEST4="echo hello world || echo how are you doing; echo I'm doing great"
TEST5="echo hello world && echo how are you doing && echo I'm doing great"
TEST6="echo hello world && FAILCOMMAND how are you doing && echo I'm doing great"
TEST7="echo hello world || FAILCOMMAND how are you doing && echo I'm doing great"

echo Test 1
echo -e $TEST1 | ./bin/rshell
echo Test 2
echo -e $TEST2 | ./bin/rshell
echo Test 3
echo -e $TEST3 | ./bin/rshell
echo Test 4
echo -e $TEST4 | ./bin/rshell
echo Test 5
echo -e $TEST5 | ./bin/rshell
echo Test 6
echo -e $TEST6 | ./bin/rshell
echo Test 7
echo -e $TEST7 | ./bin/rshell
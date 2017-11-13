#!/bin/bash
#tests test commands

TEST1="test bin/rshell"
TEST2="test -d bin"
TEST3="test -f bin/rshell && echo its a folder"
TEST4="test bin/rshellfake || echo bin/rshellfake doesn't exist"
TEST5="exit"
#TEST6="FAILCOMMAND"
#TEST7="FAILCOMMAND FAILPARAMETER"
#TEST8="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n" | ./bin/rshell


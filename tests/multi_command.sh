#!/bin/bash
#tests multi commands

TEST1="pwd; ls -a"
TEST2="echo These lines; echo should work; echo without problem"
TEST3="echo Likewise these && echo lines have; echo no issues"
TEST4="echo The next command will not execute || echo JK, program is broke; echo See?"
TEST5="echo However, these && echo have no problem && echo as they are all valid"
TEST6="echo The next command will fail; FAILCOMMAND && echo JK, program is broke"
TEST7="echo The next command will fail; FAILCOMMAND how are you doing || echo But this time, I'm fine"
TEST8="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n" | ./bin/rshell
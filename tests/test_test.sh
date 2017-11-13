#!/bin/bash
#tests test commands

TEST1="test bin/rshell"
TEST2="test -d bin; echo testing test with user flag specification"
TEST3="test -f bin/rshell && echo its a folder"
TEST4="test bin/rshellfake || echo bin/rshellfake doesn't exist"
TEST5="[ bin/rshell ]"
TEST6="[ -f bin/rshell ] && echo its a folder"
TEST7="echo testing an nonexistanct foler; [ bin/rshellfake ] || echo bin/rshellfake doesn't exist"
TEST8="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n" | ./bin/rshell


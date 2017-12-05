#!/bin/bash
#tests input redirection commands

TEST1="cat < Makefile"
TEST2="cat < Makefile;"
TEST3="cat < Makefile | echo sup"
TEST4=""
TEST5=""
TEST6=""
TEST7=""
TEST8=""
TEST9="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n$TEST9\n" | ./bin/rshell

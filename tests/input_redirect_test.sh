#!/bin/bash
#tests input redirection commands

TEST1="cat < B" #prints B
TEST2="cat A < B;" #prints A
TEST3="cat < A B A" #prints B A
TEST4="cat A B A < A" #prints A B A
TEST5="cat A B A < A B A" #prints A B A B A
TEST6="echo < B" #prints nothing
TEST7="echo A < B" #prints A
TEST8="echo A B A < A B A" #prints A B A B A
TEST9="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n$TEST9\n" | ./bin/rshell

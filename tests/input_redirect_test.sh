#!/bin/bash
#tests input redirection commands

#   A and B are valid files. Z is an invalid file.

#   To see if the tests worked correctly from a glance
#   the prints should follow an A B A B A... pattern or be empty

TEST1="cat < A" #prints A
TEST2="cat A < B" #prints A
TEST3="cat < B A B" #prints A B
TEST4="cat A B A < A" #prints A B A
TEST5="cat A B A < A B A" #prints A B A B A
TEST6="echo < B" #prints nothing
TEST7="echo A < B" #prints A
TEST8="echo A B A < A B A" #prints A B A B A
TEST9="cat < A; cat < B" #prints A B
TEST10="cat Z < A" #prints failure
TEST11="cat Z < A && cat < B" #prints failure
TEST12="cat Z < A || cat < A" #prints failure and A
TEST13="cat < B < A" #prints A
TEST14="cat A < B < B" #prints A
TEST15="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n$TEST9\n$TEST10\n$TEST11\n$TEST12\n$TEST13\n$TEST14\n$TEST15\n" | ./bin/rshell

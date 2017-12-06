#!/bin/bash
#tests append redirection commands

#   A and B are valid files. C is an output file. Z is an invalid file.

#   To see if the tests worked correctly from a glance
#   the outputs should follow an A B A B A... pattern

TEST1="cat A > ./append_test/C" #outputs A into C
TEST2="cat B >> ./append_test/C > ./append_test/E" #appends B into C
TEST3="cat A >> B >> ./append_test/C" #appends A into C
TEST4="cat B >> ./append_test/C; cat A >> ./append_test/C" #appends B and A into C
TEST5="cat ./append_test/C >> ./append_test/C" #outputs failure (input is output)
TEST6="cat ./append_test/C < A >> ./append_test/C" #outputs failure (input is output)
TEST7="cat ./append_test/C > ./append_test/D" #outputs C into D (checkpoint)
TEST8="cat B A >> ./append_test/D" #appends B A into D
TEST9="cat B A >> A B A >> A B A >> ./append_test/D" #appends B A B A B A into D
TEST10="exit"

mkdir -p append_test
echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n$TEST9\n$TEST10\n" | ./bin/rshell

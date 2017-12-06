#!/bin/bash
#tests output redirection commands

#   A and B are valid files. C-Y is an output file. Z is an invalid file.

#   To see if the tests worked correctly from a glance
#   the outputs should follow an A B A B A... pattern or be empty

TEST1="cat A > ./output_test/C" #outputs A into C
TEST2="cat A > ./output_test/D > ./output_test/E" #outputs an empty file into D and A into E
TEST3="cat B > ./output_test/F; cat A > ./output_test/F" #outputs A into F
TEST4="cat Z > ./output_test/G" #outputs an empty file into G
TEST5="cat Z > ./output_test/H && cat B > ./output_test/H" #outputs an empty file into H
TEST6="cat Z > ./ouctput_test/I || cat A > ./output_test/I" #outputs A into I
TEST7="cat < A > ./output_test/J" #outputs A into J
TEST8="cat A < B > ./output_test/K" #outputs A into K
TEST9="cat < A < B < B > ./output_test/L" #outputs A into L
TEST10="cat A B > ./output_test/M" #outputs A B into M
TEST11="cat A B > ./output_test/N A" #outpus A B A into N
TEST12="exit"

mkdir -p output_test
echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n$TEST9\n$TEST10\n$TEST11\n$TEST12\n" | ./bin/rshell

# BUGS
# TEST 2: OUTPUTTED A INTO D AND AN EMPTY FILE INTO E INSTEAD OF EMPTY FILE INTO D AND A INTO E
# TEST 4: OUTPUTTED $ INTO G INSTEAD OF EMPTY FILE
# TEST 5: OUTPUTTED MULTIPLE $ INTO H INSTEAD OF EMPTY FILE
# TEST 11: OUTPUTTED AB INTO N INSTEAD OF ABA
#!/bin/bash
#tests pipe redirection commands

#   A and B are valid files. C-Y is an output file. Z is an invalid file.

#   To see if the tests worked correctly from a glance
#   the outputs should have the A outpuy with a modified last word or be empty

TEST1="cat A | sed s/Agrammar/Legion/ > ./pipe_test/C" #outputs A of Legion into C
TEST2="cat A | sed s/Agrammar/Legion/ | sed s/Legion/Azsuna/ > ./pipe_test/D" #outputs A of Azsuna into D
TEST3="cat < A | sed s/Agrammar/Legion/ > ./pipe_test/E" #outputs A of Legion into E
#TEST4="echo -e \"exit\n\" | ./bin/rshell && cat A > ./pipe_test/F" #outputs A into F
#TEST5="echo -e \"exit\n\" | ./Z || cat A > ./pipe_test/G" #outputs A into G
TEST6="cat A | sed s/Agrammar/Legion/; cat B | sed s/Cosmic/Galatic/" #outputs A of Legion and Galatic B
TEST7="exit"

mkdir -p pipe_test
echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST6\n$TEST7\n" | ./bin/rshell
#$TEST4\n$TEST5\n

# BUGS
# Bash error with piping into exectables. Works when testing individually, not in a bash setting.
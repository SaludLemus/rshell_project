#!/bin/bash
#tests precendence commands

TEST1="echo A && echo B || echo C && echo D"
TEST2="(echo A && echo B) || (echo C && echo D)"
TEST3="(echo A && echo B || echo C && echo D)"
TEST4="(echo A && echo B || (echo C && echo D))"
TEST5="((echo A && echo B) || echo C && echo D)"
TEST6="(echo A && echo B); (echo C && echo D)"
TEST7="(((echo A && echo B || echo C && echo D)))"
TEST8="(echo A && echo B && (echo \"C && D\"))"
TEST9="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n$TEST9\n" | ./bin/rshell


#!/bin/bash
#tests test commands

TEST1="echo A && echo B || echo C && echo D"
TEST2="(echo A && echo B) || (echo C && echo D)"
TEST3="(echo A && echo B || echo C && echo D)"
TEST4="(echo A && echo B || (echo C && echo D))"
TEST5="((echo A && echo B) || echo C && echo D)"
TEST6="(echo A && echo B); (echo C && echo D)"
TEST7="echo testing an nonexistanct foler; [ bin/rshellfake ] || echo bin/rshellfake doesn't exist"
TEST8="exit"

echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n" | ./bin/rshell


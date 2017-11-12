#!/bin/bash
#tests multi commands

TEST1="pwd; ls -a"
TEST2="echo These lines; echo should work; echo without problem"
TEST3="echo Likewise these && lines have; echo no issues"
TEST4="echo The next command will not execute || echo JK, program is broke; echo See?"
TEST5="echo However, these && echo have no problem && echo as they are all valid"
TEST6="echo The next command will fail; FAILCOMMAND && echo JK, program is broke"
TEST7="echo The next command will fail; FAILCOMMAND how are you doing || echo But this time, I'm fine"

echo "Test 1: $TEST1"
echo -e $TEST1 | ./bin/rshellnew
echo -e "\nTest 2: $TEST2"
echo -e $TEST2 | ./bin/rshellnew
echo -e "\nTest 3: $TEST3"
echo -e $TEST3 | ./bin/rshellnew
echo -e "\nTest 4: $TEST4"
echo -e $TEST4 | ./bin/rshellnew
echo -e "\nTest 5: $TEST5"
echo -e $TEST5 | ./bin/rshellnew
echo -e "\nTest 6: $TEST6"
echo -e $TEST6 | ./bin/rshellnew
echo -e "\nTest 7: $TEST7"
echo -e $TEST7 | ./bin/rshellnew
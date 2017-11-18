#!/bin/bash
#tests single commands

TEST1="echo helloWorld!"
TEST2="echo CS100!"
TEST3="ls"
TEST4="ls -al"
TEST5="ls -j"
TEST6="echo \"This is me!\""
TEST7="echo \"echo Print Me!\""
TEST8="pwd"
TEST9="cal 4 2009"
TEST10="echa AB"
TEST11="cal"
TEST12="git"
TEST13="git status"
TEST14="man"
TEST15="date"
TEST16="exit"

echo "Single Command Test"
echo -e "$TEST1\n$TEST2\n$TEST3\n$TEST4\n$TEST5\n$TEST6\n$TEST7\n$TEST8\n$TEST9\n$TEST10\n$TEST11\n$TEST12\n$TEST13\n$TEST14\n$TEST15\n$TEST16\n" | ./bin/rshell

TEST17="echo A && echo B"
TEST18="echo A || echo B"
TEST19="echo A; echo B"
TEST20="ls -j && echo A"
TEST21="ls -j || echo A"
TEST22="ls -j; echo A"
TEST23="cal 4 2009 && echo This is a date || echo b"
TEST24="echo \"A || B\" && echo PrintHere"
TEST25="echo \"A && B\" \"A || B\"; echo PrintHERE"
TEST26="pwd fileNotExist || echo Yes && echo \"Temp || \""
TEST27="exit"

echo ""
echo "Multi Command Test"
echo -e "$TEST17\n$TEST18\n$TEST19\n$TEST20\n$TEST21\n$TEST22\n$TEST23\n$TEST24\n$TEST25\n$TEST26\n$TEST27\n" | ./bin/rshell

TEST28="echo A #echo B"
TEST29="echo A #&& echo B"
TEST30="echo \"Testing comments inside # Should Print Me\""
TEST31="echo A && echo B #&& echo C"
TEST32="echo A #; echo B"
TEST33="echo A ##### echo B"
TEST34="ls #-a"
TEST35="echo \"#\""
TEST36="echo #"
TEST37="cal #9 2001"
TEST38="exit"

echo ""
echo "Comments Test"
echo -e "$TEST28\n$TEST29\n$TEST30\n$TEST31\n$TEST32\n$TEST33\n$TEST34\n$TEST35\n$TEST36\n$TEST37\n$TEST38\n" | ./bin/rshell
#!/bin/bash
#tests single commands

TEST1="mkdir -p DIR; cd ./DIR; pwd; cd ..; rm DIR"

echo $TEST1 | ./bin/rshell
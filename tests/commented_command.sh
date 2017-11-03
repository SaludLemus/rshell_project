#!/bin/bash
#tests multiple commands

TEST1="mkdir -p DIR; cd ./DIR; pwd; cd ..; rm DIR"

echo $TEST1 | ./bin/rshell
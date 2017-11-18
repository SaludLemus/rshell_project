# rshell-wizard

<h2 id="Overview">Overview</h2>

<h3 id="Introduction">Introduction</h3>
Run multiple PATH executables with success and failure logic connectors between executables alongside commenting.

<h3 id="Getting Started">Getting Started</h3>
Getting started is very easy. Once you are in the main directory, execute the following command.

    make
    
And that is it. An executable labeled "rshell" will appear in the bin directory. You are set!


<h3 id="Syntax">Syntax</h3>

<h4 id="Logic Connectors">Logic Connectors</h4>
If you desire to add logic connectors in your executables, then use "&&", "||", and ";" between commands. For example:

    $ mkdir bin; echo Directory already exists.
    $ mkdir bin && echo Created new directory
    $ mkdir bin || echo Directory already exists.
    
&& : The following command will be executed if the previous succeeded.

|| : The following command will be executed if the previous failed.

;  : The following command will be executed regardless of the previous' result.

There are no limits to the number of commands that can be chained using these and any other connectors.

<h4 id="Parentheses">Parentheses</h4>
Use precedence operators by using parentheses (), this will change the precedence of the returns of commands, connectors, and chains of connectors. For example:

    $ (mkdir bin && echo A bin directory has been created) || (mkdir newbin && echo A new bin directory has been created)
    
The second set of commands will execute if first set of commands fail. It really is that simple.

<h4 id="Special Commands">Special Commands</h4>
If you want to exit out of the rshell, "exit" will terminate the program. For example:

    $ echo hello world; exit; mkdir bin

Next, if you want to use an equivalent terminal command of "test", "[ ]" can be explicitly used around the command itself. For example:

    Both are equivalent!
    $ test -e /home/user/Documents
    $ [ -e /home/user/Documents ]

<h4 id ="Commenting">Commenting</h4>
Documentation is very important, so you are able to add comments into your command lines.

    These are same!
    $ mkdir test; rm ./test #Testing mkdir and rm; echo hello
    $ mkdir test; rm ./test
    
Everything after the '#' will not be included in the arguments and such, will not interfere with your executables.

<h2 id="How it works">How it works</h2>
Our rshell stores the commands in a binary tree like so:

    $ echo hello world && mkdir bin || echo this is a test

![tree_diagram](https://user-images.githubusercontent.com/22006152/32976075-cc52a326-cc07-11e7-9f01-858e5c9ac62a.png)

Now if parentheses are included in the commands, then the binary tree would look like:

    $ (echo A && (echo B || echo C))

![tree_diagram_with_parentheses](https://user-images.githubusercontent.com/22006152/32976154-dd5ab324-cc08-11e7-9a37-e7aa46fe1e38.png)

<h2 id="Debugging">Debugging</h2>
Debugging should go here.

<h2 id="Known Bugs">Known Bugs</h2>

The program is currently a work in progress, so there will be bugs sadly. 

List of known bugs:

Syntax is very strict. Extra spaces will crash the parser.

An unequal amount of parathesis will also crash the parser.

# rshell-wizard

<h2 id="Overview">Overview</h2>

<h3 id="Introduction">Introduction</h3>
Run multiple PATH executables with logic and I/O redirection connectors alongside commenting and precedence.

<h3 id="Getting Started">Getting Started</h3>
Getting started is very easy. Once you are in the main directory, execute the following command in the terminal.

    make
    ./bin/rshell
    
You are set!

<h3 id="How to Use">How to Use</h3>

<h4 id="Logic Connectors">Logic Connectors</h4>
Add logic connectors to incorporate, well, logic into a stream of executables.

;     The following command will be executed regardless of the previous' result.<br>
&&    The following command will be executed if the previous succeeded.<br>
||    The following command will be executed if the previous failed.

    $ mkdir bin; echo Continue as normal.
    $ mkdir bin && echo Created new directory.
    $ mkdir bin || echo Directory already exists.
    
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
The rshell utilizes a binary tree to store its commands, like so:

    $ echo hello world && mkdir bin || echo this is a test

The commands will be executed in the standard inorder procedure.

![tree_diagram](https://user-images.githubusercontent.com/22006152/32976075-cc52a326-cc07-11e7-9f01-858e5c9ac62a.png)

When parathesis are involved, the parser will create roots based on parathesised commands and simply set them as regular nodes, like so:

    $ echo A && (echo B || echo C)

![tree_diagram_with_parentheses](https://user-images.githubusercontent.com/22006152/32976154-dd5ab324-cc08-11e7-9a37-e7aa46fe1e38.png)

<h2 id="Known Bugs">Known Bugs</h2>

The program is currently a work in progress, so there will be bugs sadly. 

List of known bugs:

Syntax is very strict. Extra spaces will crash the parser.

An unequal amount of parentheses will also crash the parser.

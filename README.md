# rshell-wizard

<h2 id="Overview">Overview</h2>

<h3 id="Introduction">Introduction</h3>
Run multiple PATH executables with success and failure logic connectors between executables alongside commenting.

<h3 id="Basics">Basics</h3>
The usage is intuitive as it is based off basic terminal commands and logic code. For example:

    $ ls -a
    $ echo hello
    $ mkdir test
    
can be condensed into one single line:

    $ ls -a; echo hello; mkdir test

<h3 id="Logic">Logic</h3>
If you desire to add logic connectors in your executables, then use "&&" and "||" between commands. For example:

    $ mkdir bin && echo Created new directory
    
will attempt to create the directory bin and will only execute the echo command if the previous command executed successfully. Likewise:

    $ mkdir bin || echo Directory already exists.
    
will attempt to create the directory bin; however, the echo will only execute if the previous command failed.

There is no limit to the number of commands that be chained using these and any other connectors.

<h3 id="Commenting">Commenting</h3>
Documentation is very important, so you are able to add comments into your command lines.

    These are same!
    $ mkdir test; rm ./test #Testing mkdir and rm; echo hello
    $ mkdir test; rm ./test
    
Everything after the '#' will not be included in the arguments and such, will not interfere with your executables.

<h2 id="Known Bugs">Known Bugs</h2>

The program is currently a work in progress, so there will be bugs sadly. 

List of known bugs:
    With bash piping, empty commands will not create a newline. Unsure if this is a bash issue or a coding issue.

# rshell-wizard

<h2 id="Overview">Overview</h2>

<h3 id="Introduction">Introduction</h3>
Run multiple PATH executables with success and failure logic connectors between executables alongside commenting. Further determine whether a given PATH exists by using specific flags.

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

<h3 id="Test">Test</h3>
The test command enables to determine whether a specified PATH does or does not exist by using either: -e, -f, or -d as flags, which will output "(True)" or "(False)" to the console.
NOTE: test is equivalent to square brackets ([])

    Both are equivalent!
    $ test -e /home/user/Documents
    $ [ -e /home/user/Documents ]

If the specified PATH exists, "(True)" will be sent to the console; otherwise, "(False)" will be displayed.

As stated before, test can also be extended to work along with basic terminal commands and connectors:

    $ test -e /home/user/Documents && echo this directory exists

Assuming that the PATH exits, "(True)" will be displayed, and since the left expression is true, "this directory exists" will also be sent to the console.

<h4 id="Flag e">Flag e/h3>
If the flag "-e" is encountered, this will check whether the PATH exists.
NOTE: If a flag is not encountered, "-e" flag will be used by default:

    Both pieces of code are equivalent!
    $ test -e /home/user/Documents
    $ test /home/user/Documents

If the PATH exists, "(True)" will be displayed, else "(False)" will be displayed.

<h4 id="Flag f">Flag f/h4>
If the flage "-f" is used, this will check if the PATH exists, AND if it is a regular file

    $ test -f /home/user/Documents/main.cpp

If the PATH exists AND it is a regular file, "(True)" will be displayed; otherwise, "(False)" will be displayed.

<h4 id="Flag d">Flag d/h4>
Now for the flag "-d", this will check whether the PATH exists, AND if it is a directory.

    $ test -d /home/user/Pictures
    
If the PATH exists, AND if it is a directory, then "(True)" will be sent to the console; otherwise, "(False)" will be displayed.

<h3 id="Precedence Operators">Precedence Operators</h3>
Now with the introduction of precedence operators by using parentheses (), this will change the precedence of the returns of commands, connectors, and chains of connectors:
For example:

    $ test -d /home/user/Documents/Projects && echo PATH exists and is a directory || echo PATH is does not exist && echo PATH is not directory

Can be manipulated with precdence operators such as:

    $ (test -d /home/user/Documents/Projects && echo PATH exists and is a directory) || (echo PATH is does not exist && echo PATH is not directory)
    
If the first set of parentheses returns true via the AND connector, then the OR connector's right expression, which is now condensed into a group via parentheses, will not be executed. Otherwise, if the first set of parentheses returns false, then the right expression of the OR connector will be executed.

<h2 id="Known Bugs">Known Bugs</h2>

The program is currently a work in progress, so there will be bugs sadly. 

List of known bugs:
    With bash piping, empty commands will not create a newline. Unsure if this is a bash issue or a coding issue.

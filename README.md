# rshell-wizard

<h2 id="Overview">Overview</h2>

<h3 id="Introduction">Introduction</h3>
Run multiple PATH executables with logic and I/O redirection connectors alongside commenting and precedence. 

This was created by two UCR students, Jose Garcia and Salud Salad, as a sememster long CS project. Thanks to UCR, professors, and the library for giving us the resources and knowledge to accomplish this project.

<h3 id="Getting Started">Getting Started</h3>
Getting started is very easy. Once you are in the main directory, execute the following command in the terminal.

    make
    ./bin/rshell
    
You are set!

<h3 id="How to Use the Connectors">How to Use the Connectors</h3>

<h4 id="Logic">Logic</h4>
Add logic connectors to incorporate, well, logic into a stream of executables.

<table style="width:100%">
  <tr>
  	<td>;</td>
    <td>The following command will be executed regardless of the previous' result.</td>
  </tr>
  <tr>
    <td>&&</td>
    <td>The following command will be executed if the previous succeeded.</td>
  </tr>
  <tr>
    <td>||</td>
    <td>The following command will be executed if the previous failed.</td>
  </tr>
</table>

    $ mkdir bin; echo Continue as normal.
    $ mkdir bin && echo Created new directory.
    $ mkdir bin || echo Directory already exists.

<h4 id="I/O Redirection">I/O Redirection</h4>
Add I/O redirection connectors to redirect the input and output of the executable's results.

<table style="width:100%">
  <tr>
  	<td><</td>
    <td>The previous command will read input from the following file.</td>
  </tr>
  <tr>
    <td>></td>
    <td>The following file will write output from the result of the previous command.</td>
  </tr>
  <tr>
    <td>>></td>
    <td>The following file will append output from the result of the previous command.</td>
  </tr>
    <tr>
    <td>|</td>
    <td>The result of the previous command will become the input to the following command.</td>
  </tr>
</table>

    $ cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2

<h3 id="Special Syntax">Special Syntax</h3>

<h4 id="Precedence">Precedence</h4>
Add precendence to group a set of executables and connectors. Use parathesis to accomplish this and further improve your options.

    $ (mkdir bin && echo A bin directory has been created) || (mkdir newbin && echo A new bin directory has been created)

<h4 id ="Comments">Comments</h4>
Add comments to document your command lines. Use (#) and anything after it will be ignored.

    $ mkdir test; rm ./test #Testing mkdir and rm

<h4 id="Special Commands">Special Commands</h4>
If you want to exit out of the rshell, special command "exit" will terminate the program immediately.

    $ echo hello world; exit

If you want to use an equivalent terminal command of "test", "[ ]" can be explicitly used around the command itself.

    Both are equivalent!
    $ test -e /home/user/Documents
    $ [ -e /home/user/Documents ]


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

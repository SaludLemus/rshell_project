# rshell-wizard

<h2 id="Overview">Overview</h2>

<h3 id="Introduction">Introduction</h3>
<p>Run multiple PATH executables with logic and I/O redirection connectors alongside commenting and precedence. </p>
<p>This was created by two UCR students, Jose Garcia and Salud Salad, as a sememster long CS project. Thanks to UCR, professors, and the library for giving us the resources and knowledge to accomplish this project.</p>

<h3 id="Getting Started">Getting Started</h3>
Getting started is very easy. Once you are in the main directory, execute the following command in the terminal.

    make
    ./bin/rshell
    
You are set!

<h3 id="Connectors">Connectors</h3>

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


<h2 id="How the rshell works">How the rshell works</h2>
<h3 id="Parser">Parser</h3>
First, the parser will attempt to create a binary tree from the rshell terminal input. Connectors will become the root nodes while the executables will become the leaf nodes.

<img src="https://i.imgur.com/u8su4tv.png" alt="Binary Tree 1">

<p>The parser follows a strict but repeative pattern until it reaches the end of line.</p>
<p>GetCommand() -> GetConnector() -> GetCommand() -> GetConnector() -> GetCommand() -> ... -> GetCommand()</p>
<p>In the case of precedence, the parser will recursively create a new binary tree from the contents inside the parathesis and the result will be treated as a Command.</p>

<img src="https://i.imgur.com/lgaguHI.png" alt="Binary Tree 2">

If the parser fails at any point, rshell will exit immediately and no executable will be called.

<h3 id="Execute">Execute</h3>
<p>Once the parser returns successfully, execute() will be called from the root node. From there, the Base nodes will run execute in the inorder pattern. As executables are always leaf nodes, they will be performing the execvp() to run its commands and flags.</p>
<p>While logic connectors will follow the inorder pattern, I/O redirection connectors divert by opening files based on the right node's command data. As such, precedence is impossible with I/O redirection.</p>
<p>Execute() will not stop until it reaches finishes back in the root node. So while the parser will stop improper syntax, the execute will not stop at any mispellings. Be sure to proofread your rshell scripts!</p>


<h2 id="Known Bugs">Known Bugs</h2>

Syntax is very strict. Extra spaces will crash the parser.

Extra connectors at the end of a line, while meaningless on paper, will crash the parser.

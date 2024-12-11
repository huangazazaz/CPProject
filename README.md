# CS323 Project
黄增荣 RyanTang 何文孝 黄少霖

## Lexical Analysis

We use **Flex** for lexical analysis; the token specification can be find in [token.txt](https://github.com/huangazazaz/CPProject/blob/main/token.txt).

We support **single and multiple line comments**, **compound assignment operators** like '+=', **binary operators** like '^', **mod**, **for loop** and **primitive type** bool.

## Syntax Analysis

For syntax analysis, we used **Bison** to generate a parser for our language. The grammar rules are defined to handle typical programming constructs such as loops, conditionals, and function declarations. The following are key elements of our grammar:

- **Expressions**: Arithmetic operations, logical operations, and assignments.
- **Control Flow**: `if` statements, `else` branches, and `while|for` loops.
- **Function Handling**: Definitions, calls, and return statements.
- **Ternary**: The ternary conditional operator (a ? b : c).
- **Scope checking**: Check variable in different scope.

The generated parser efficiently handles errors by providing meaningful error messages and recovery options.

Our parser structure can be find in [syntax.txt](https://github.com/huangazazaz/CPProject/blob/main/syntax.txt).

Now we have completed the syntax, lexical, semantic analysis and the generation of intercode.

We prepared an IR simulator so that you can run your generated TACs. It is available on our GitHub repository. It is built with a Python module, urwid. If you want to run it on your own computer, make sure you have installed urwid. Note that urwid does notsupport Windows environment. Besides, this simulator is buggy. Don’t be surprised if you see abnormal behaviors :)

If you want to run an IR program test_a.ir with three integers, 1, 9, and 42 as input, you may simply type the following command: 
`irsim test_a.ir-i 1,9,42`

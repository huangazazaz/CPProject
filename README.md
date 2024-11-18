# CS323 Project
黄增荣 RyanTang 何文孝 黄少霖

## Lexical Analysis

We use **Flex** for lexical analysis; the token specification can be find in [token.txt](https://github.com/huangazazaz/CPProject/token.txt).

We support **single and multiple line comments**, **compound assignment operators** like '+=', **binary operators** like '^', **mod**, **for loop** and **primitive type** bool.

## Syntax Analysis

For syntax analysis, we used **Bison** to generate a parser for our language. The grammar rules are defined to handle typical programming constructs such as loops, conditionals, and function declarations. The following are key elements of our grammar:

- **Expressions**: Arithmetic operations, logical operations, and assignments.
- **Control Flow**: `if` statements, `else` branches, and `while|for` loops.
- **Function Handling**: Definitions, calls, and return statements.

The generated parser efficiently handles errors by providing meaningful error messages and recovery options.

Our parser structure can be find in [syntax.txt](https://github.com/huangazazaz/CPProject/syntax.txt).

Now we have completed most of the syntax and lexical analysis for the language and have also implemented parts of semantic analysis. This includes type checking to ensure operations are performed on compatible types, as well as validations for undefined or redeclared variables.

Currently, we are working on extending the language with features such as the ternary conditional operator (a ? b : c) and range checks. 

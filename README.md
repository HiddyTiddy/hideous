# hideous
random projects

## ships.cpp
Program to generate perfect ships for the --ship command of the [Yggdrasil Discord Bot](https://ygg.fun/)

research and development time: 18th of April – 20th of April

## factorize.cpp
Command line utility to factorize a given number.

example usage:
```bash
$ factorize 12345
3 5 823

$ echo "12345" | factorize 
3 5 823
```

Date: Feb 22


## brainfuck.cpp
Command line interpreter for [Brainfuck](https://esolangs.org/wiki/Brainfuck)

```bash
brainfuck "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."
echo "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++." | brainfuck
```

Date: `i forgor`

## bfc.cpp
Compiler for [Brainfuck](https://esolangs.org/wiki/Brainfuck)

```bash
echo "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++." > source.bf
bfc source.bf -o hello
```

Date: 25.09.21

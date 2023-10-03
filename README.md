# make-tiny-compiler-from-scratch
make-tiny-compiler-from-scratch

I studied how to make a tiny compiler from scratch 
based on https://austinhenley.com/blog/teenytinycompiler1.html

The compiler includes 3 parts:

Lexer(parse input code file to tokens (words)) -> Parser (check the tokens based on Grammar) -> Emitter (generate the target "language")

Here is the Grammar:

  program ::= {statement}
  statement ::= "PRINT" (expression | string) nl
      | "IF" comparison nl {statement} nl "ELSE" nl {statement} nl "ENDIF" nl
      | "WHILE" comparison nl {statement} "ENDWHILE" nl
      | "PASS" nl
      | "LET" ident "=" expression nl
      | "INPUT" ident nl
  comparison ::= expression (("==" | "!=" | ">" | ">=" | "<" | "<=") expression)+
  expression ::= term {( "-" | "+" ) term}
  term ::= unary {( "/" | "*" ) unary}
  unary ::= ["+" | "-"] primary
  primary ::= number | ident
  nl ::= '\n'+

The compiler is written in C++ that compile your language to Python:
Example:
Your language:

IF nums > 0
    PRINT "not zero"
ELSE
    IF nums == 0
        PRINT "zero"
    ENDIF
ENDIF

To Python:

if nums > 0:
	print ("not zero")
else:
	if nums == 0:
		print ("zero")

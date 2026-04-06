%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "prac.h"
%}

%option noyywrap
%option yylineno
%option noinput
%option nounput
%option outfile="lex.yy.c"

/* Regular Definitions */
DIGIT                   [0-9]
NONZERO_DIGIT          [1-9]
IDENTIFIER_NONDIGIT    [a-zA-Z_]
SIGN                   [+-]
ESCAPE_SEQUENCE        \\['"?\\abfnrtv]
S_CHAR                 [^"\\\n]|{ESCAPE_SEQUENCE}
C_CHAR                 [^'\\\n]|{ESCAPE_SEQUENCE}

%%

    /* Keywords */
"char"|"else"|"for"|"if"|"int"|"return"|"void"    { return KEYWORD; }

    /* Identifiers */
{IDENTIFIER_NONDIGIT}({IDENTIFIER_NONDIGIT}|{DIGIT})*    { return IDENTIFIER; }

    /* Integer Constants */
{SIGN}?{NONZERO_DIGIT}{DIGIT}*    { return INTEGER_CONSTANT; }
"0"                               { return INTEGER_CONSTANT; }

    /* Character Constants */
\'({C_CHAR})\'    { return CHARACTER_CONSTANT; }

    /* String Literals */
\"({S_CHAR})*\"    { return STRING_LITERAL; }

    /* Operators */
"+"     { return OPERATOR; }  /* Arithmetic Operators */
"-"     { return OPERATOR; }
"*"     { return OPERATOR; }
"/"     { return OPERATOR; }
"%"     { return OPERATOR; }

"<"     { return OPERATOR; }  /* Relational Operators */
">"     { return OPERATOR; }
"<="    { return OPERATOR; }
">="    { return OPERATOR; }
"=="    { return OPERATOR; }
"!="    { return OPERATOR; }

"&&"    { return OPERATOR; }  /* Logical Operators */
"||"    { return OPERATOR; }
"!"     { return OPERATOR; }

"?"     { return OPERATOR; }  /* Conditional Operator */
":"     { return OPERATOR; }

"&"     { return OPERATOR; }  /* Pointer Operators */
"->"    { return OPERATOR; }

"="     { return OPERATOR; }  /* Assignment Operator */

    /* Punctuators */
"["     { return PUNCTUATOR; }
"]"     { return PUNCTUATOR; }
"("     { return PUNCTUATOR; }
")"     { return PUNCTUATOR; }
"{"     { return PUNCTUATOR; }
"}"     { return PUNCTUATOR; }
";"     { return PUNCTUATOR; }
","     { return PUNCTUATOR; }

    /* Comments */
"/*"([^*]|"*"+[^*/])*"*"+"/"    { return COMMENT; }
"//".*\n                         { return COMMENT; }

    /* Whitespace */
[ \t\n\r]+    { /* Skip whitespace */ }

    /* Invalid */
.    { return INVALID; }

%%

const char* get_token_name(int token) {
    switch(token) {
        case KEYWORD: return "KEYWORD";
        case IDENTIFIER: return "IDENTIFIER";
        case INTEGER_CONSTANT: return "INTEGER_CONSTANT";
        case CHARACTER_CONSTANT: return "CHARACTER_CONSTANT";
        case STRING_LITERAL: return "STRING_LITERAL";
        case OPERATOR: return "OPERATOR";
        case PUNCTUATOR: return "PUNCTUATOR";
        case COMMENT: return "COMMENT";
        default: return "INVALID";
    }
}
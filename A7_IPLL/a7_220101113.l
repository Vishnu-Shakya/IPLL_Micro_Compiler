%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

extern int yylex();
void count(void);
int comment(void);
%}

D   [0-9]
L   [a-zA-Z_]
H   [a-fA-F0-9]
E   [Ee][+-]?{D}+
FS  (f|F|l|L)
IS  (u|U|l|L)*

%%
"/*"        { comment(); }
"//".*      { /* consume single-line comment */ }

"return"    { count(); return(RETURN); }
"void"      { count(); return(VOID); }
"float"     { count(); return(FLOAT); }
"integer"   { count(); return(INTEGER); }
"char"      { count(); return(CHAR); }
"for"       { count(); return(FOR); }
"const"     { count(); return(CONST); }
"while"     { count(); return(WHILE); }
"bool"      { count(); return(BOOL); }
"if"        { count(); return(IF); }
"do"        { count(); return(DO); }
"else"      { count(); return(ELSE); }
"begin"     { count(); return(MC_BEGIN); }
"end"       { count(); return(END); }

{L}({L}|{D})*   { 
                    count(); 
                    yylval.sval = strdup(yytext);
                    return(IDENTIFIER); 
                }

[1-9]{D}*|[0]      { 
                    count(); 
                    yylval.ival = atoi(yytext);
                    return(INTEGER_CONSTANT); 
                }

{D}+{E}{FS}?    { 
                    count(); 
                    yylval.fval = atof(yytext);
                    return(FLOATING_CONSTANT); 
                }

{D}*"."{D}+{E}?{FS}?  { 
                    count(); 
                    yylval.fval = atof(yytext);
                    return(FLOATING_CONSTANT); 
                }

{D}+"."{D}*{E}?{FS}?  { 
                    count(); 
                    yylval.fval = atof(yytext);
                    return(FLOATING_CONSTANT); 
                }

'(\\.|[^\\'\n])+' { 
                    count(); 
                    yylval.sval = strdup(yytext);
                    return(CHARACTER_CONSTANT); 
                }

\"(\\.|[^\\"\n])*\"  { 
                    count(); 
                    yylval.sval = strdup(yytext);
                    return(STRING_LITERAL); 
                }

"->"        { count(); return(ARROW); }
"++"        { count(); return(INCREMENT); }
"--"        { count(); return(DECREMENT); }
"&"         { count(); return(AMPERSAND); }
"*"         { count(); return(ASTERISK); }
"+"         { count(); return(PLUS); }
"-"         { count(); return(MINUS); }
"!"         { count(); return(EXCLAMATION); }
"/"         { count(); return(FORWARD_SLASH); }
"%"         { count(); return(PERCENT); }
"<<"        { count(); return(LEFT_SHIFT); }
">>"        { count(); return(RIGHT_SHIFT); }
"<"         { count(); return(LESS_THAN); }
">"         { count(); return(GREATER_THAN); }
"<="        { count(); return(LESS_THAN_EQUAL); }
">="        { count(); return(GREATER_THAN_EQUAL); }
"=="        { count(); return(EQUAL_EQUAL); }
"!="        { count(); return(NOT_EQUAL); }
"^"         { count(); return(CARET); }
"|"         { count(); return(PIPE); }
"&&"        { count(); return(LOGICAL_AND); }
"||"        { count(); return(LOGICAL_OR); }
"?"         { count(); return(QUESTION_MARK); }
":"         { count(); return(COLON); }
";"         { count(); return(SEMICOLON); }
"="         { count(); return(ASSIGN); }
","         { count(); return(COMMA); }
"("         { count(); return(LP); }
")"         { count(); return(RP); }
"["         { count(); return('['); }
"]"         { count(); return(']'); }

[ \t\v\n\f]     { count(); }
.               { /* ignore bad characters */ }

%%

int yywrap(void) {
    return 1;
}

/* Handle comments */
int comment(void) {
    char c, prev = 0;
    
    while ((c = input()) != 0) {
        if (c == '/' && prev == '*')
            return 0;
        prev = c;
    }
    
    printf("Error: unterminated comment\n");
    return 0;
}

/* Count characters to track position in source */
void count(void) {
    int i;
    
    for (i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            /* track line numbers */
        }
    }
}
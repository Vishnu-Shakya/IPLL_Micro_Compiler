#ifndef PRAC_H
#define PRAC_H

// Token codes
typedef enum {
    KEYWORD = 1,
    IDENTIFIER,
    INTEGER_CONSTANT,
    CHARACTER_CONSTANT,
    STRING_LITERAL,
    OPERATOR,    // Added OPERATOR token type
    PUNCTUATOR,
    COMMENT,
    INVALID
} TokenType;

// Function declarations
const char* get_token_name(int token);
int yylex(void);

// External variables from Flex
extern char* yytext;
extern int yylineno;
extern FILE* yyin;

#endif
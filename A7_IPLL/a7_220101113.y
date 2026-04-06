%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbol table structure
typedef struct symbol {
    char *name;
    char *type;
    int scope;
    struct symbol *next;
} Symbol;

Symbol *symbolTable = NULL;

// Function prototypes
void addSymbol(char *name, char *type, int scope);
Symbol *findSymbol(char *name, int scope);
void printSymbolTable();
void yyerror(char *s);
int yylex();

// Global variables
int current_scope = 0;
%}

%union {
    int ival;
    float fval;
    char *sval;
    char *type;
}

/* Token declarations */
%token <sval> IDENTIFIER
%token <ival> INTEGER_CONSTANT
%token <fval> FLOATING_CONSTANT
%token <sval> CHARACTER_CONSTANT
%token <sval> STRING_LITERAL

/* Keywords */
%token RETURN VOID FLOAT INTEGER CHAR FOR CONST WHILE BOOL IF DO ELSE MC_BEGIN END

/* Operators and punctuators */
%token ARROW INCREMENT DECREMENT AMPERSAND ASTERISK PLUS MINUS EXCLAMATION
%token FORWARD_SLASH PERCENT LEFT_SHIFT RIGHT_SHIFT LESS_THAN GREATER_THAN LP RP
%token LESS_THAN_EQUAL GREATER_THAN_EQUAL EQUAL_EQUAL NOT_EQUAL CARET
%token PIPE LOGICAL_AND LOGICAL_OR QUESTION_MARK COLON SEMICOLON ASSIGN COMMA

/* Define operator precedence and associativity */
%right ASSIGN
%right QUESTION_MARK COLON
%left LOGICAL_OR
%left LOGICAL_AND
%left PIPE
%left CARET
%left AMPERSAND
%left EQUAL_EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_THAN_EQUAL GREATER_THAN_EQUAL
%left LEFT_SHIFT RIGHT_SHIFT
%left PLUS MINUS
%left ASTERISK FORWARD_SLASH PERCENT
%right EXCLAMATION INCREMENT DECREMENT
%left ARROW

/* Define the starting non-terminal */
%start translation_unit

%%

/* Grammar rules */

/* 1. Expressions */
expression
    : assignment_expression { printf("Reduction: expression -> assignment_expression\n"); }
    ;

assignment_expression
    : conditional_expression { printf("Reduction: assignment_expression -> conditional_expression\n"); }
    | unary_expression ASSIGN assignment_expression { printf("Reduction: assignment_expression -> unary_expression ASSIGN assignment_expression\n"); }
    ;

conditional_expression
    : logical_OR_expression { printf("Reduction: conditional_expression -> logical_OR_expression\n"); }
    | logical_OR_expression QUESTION_MARK expression COLON conditional_expression { printf("Reduction: conditional_expression -> logical_OR_expression QUESTION_MARK expression COLON conditional_expression\n"); }
    ;

logical_OR_expression
    : logical_AND_expression { printf("Reduction: logical_OR_expression -> logical_AND_expression\n"); }
    | logical_OR_expression LOGICAL_OR logical_AND_expression { printf("Reduction: logical_OR_expression -> logical_OR_expression LOGICAL_OR logical_AND_expression\n"); }
    ;

logical_AND_expression
    : equality_expression { printf("Reduction: logical_AND_expression -> equality_expression\n"); }
    | logical_AND_expression LOGICAL_AND equality_expression { printf("Reduction: logical_AND_expression -> logical_AND_expression LOGICAL_AND equality_expression\n"); }
    ;

equality_expression
    : relational_expression { printf("Reduction: equality_expression -> relational_expression\n"); }
    | equality_expression EQUAL_EQUAL relational_expression { printf("Reduction: equality_expression -> equality_expression EQUAL_EQUAL relational_expression\n"); }
    | equality_expression NOT_EQUAL relational_expression { printf("Reduction: equality_expression -> equality_expression NOT_EQUAL relational_expression\n"); }
    ;

relational_expression
    : additive_expression { printf("Reduction: relational_expression -> additive_expression\n"); }
    | relational_expression LESS_THAN additive_expression { printf("Reduction: relational_expression -> relational_expression LESS_THAN additive_expression\n"); }
    | relational_expression GREATER_THAN additive_expression { printf("Reduction: relational_expression -> relational_expression GREATER_THAN additive_expression\n"); }
    | relational_expression LESS_THAN_EQUAL additive_expression { printf("Reduction: relational_expression -> relational_expression LESS_THAN_EQUAL additive_expression\n"); }
    | relational_expression GREATER_THAN_EQUAL additive_expression { printf("Reduction: relational_expression -> relational_expression GREATER_THAN_EQUAL additive_expression\n"); }
    ;

additive_expression
    : multiplicative_expression { printf("Reduction: additive_expression -> multiplicative_expression\n"); }
    | additive_expression PLUS multiplicative_expression { printf("Reduction: additive_expression -> additive_expression PLUS multiplicative_expression\n"); }
    | additive_expression MINUS multiplicative_expression { printf("Reduction: additive_expression -> additive_expression MINUS multiplicative_expression\n"); }
    ;

multiplicative_expression
    : unary_expression { printf("Reduction: multiplicative_expression -> unary_expression\n"); }
    | multiplicative_expression ASTERISK unary_expression { printf("Reduction: multiplicative_expression -> multiplicative_expression ASTERISK unary_expression\n"); }
    | multiplicative_expression FORWARD_SLASH unary_expression { printf("Reduction: multiplicative_expression -> multiplicative_expression FORWARD_SLASH unary_expression\n"); }
    | multiplicative_expression PERCENT unary_expression { printf("Reduction: multiplicative_expression -> multiplicative_expression PERCENT unary_expression\n"); }
    ;

unary_operator
    : AMPERSAND { printf("Reduction: unary_operator -> AMPERSAND\n"); }
    | ASTERISK { printf("Reduction: unary_operator -> ASTERISK\n"); }
    | PLUS { printf("Reduction: unary_operator -> PLUS\n"); }
    | MINUS { printf("Reduction: unary_operator -> MINUS\n"); }
    | EXCLAMATION { printf("Reduction: unary_operator -> EXCLAMATION\n"); }
    | INCREMENT { printf("Reduction: unary_operator -> INCREMENT\n"); }
    | DECREMENT { printf("Reduction: unary_operator -> DECREMENT\n"); }
    ;

unary_expression
    : postfix_expression { printf("Reduction: unary_expression -> postfix_expression\n"); }
    | unary_operator unary_expression { printf("Reduction: unary_expression -> unary_operator unary_expression\n"); }
    | unary_expression INCREMENT{ printf("Reduction: unary_expression -> unary_expression INCREMENT\n"); }
    | unary_expression DECREMENT{ printf("Reduction: unary_expression -> unary_expression DECREMENT\n"); }
    ;

argument_expression_list_opt
    : argument_expression_list { printf("Reduction: argument_expression_list_opt -> argument_expression_list\n"); }
    | /* empty */ { printf("Reduction: argument_expression_list_opt -> empty\n"); }
    ;

argument_expression_list
    : assignment_expression { printf("Reduction: argument_expression_list -> assignment_expression\n"); }
    | argument_expression_list COMMA assignment_expression { printf("Reduction: argument_expression_list -> argument_expression_list COMMA assignment_expression\n"); }
    ;

postfix_expression
    : primary_expression { printf("Reduction: postfix_expression -> primary_expression\n"); }
    | postfix_expression '[' expression ']' { printf("Reduction: postfix_expression -> postfix_expression '[' expression ']'\n"); }
    | postfix_expression LP argument_expression_list_opt RP { printf("Reduction: postfix_expression -> postfix_expression LP argument_expression_list_opt RP\n"); }
    | postfix_expression ARROW IDENTIFIER { printf("Reduction: postfix_expression -> postfix_expression ARROW IDENTIFIER\n"); }
    ;

primary_expression
    : IDENTIFIER {
        printf("Reduction: primary_expression -> IDENTIFIER\n");
        Symbol *s = findSymbol($1, current_scope);

        if (s == NULL) {
            // Check in global scope
            for(int i=current_scope-1;i>=0;i=i-1){
            s = findSymbol($1, i);
            if (s != NULL) {
                break;
            }
            }
          if (s == NULL) {
            printf("Warning: Undeclared identifier %s\n", $1);
        }
        }
    }
    | INTEGER_CONSTANT { printf("Reduction: primary_expression -> INTEGER_CONSTANT\n"); }
    | FLOATING_CONSTANT { printf("Reduction: primary_expression -> FLOATING_CONSTANT\n"); }
    | CHARACTER_CONSTANT { printf("Reduction: primary_expression -> CHARACTER_CONSTANT\n"); }
    | STRING_LITERAL { printf("Reduction: primary_expression -> STRING_LITERAL\n"); }
    | LP expression RP { printf("Reduction: primary_expression -> LP expression RP\n"); }
    ;

/* 2. Declarations */
declaration
    : type_specifier init_declarator SEMICOLON {
        printf("Reduction: declaration -> type_specifier init_declarator ';'\n");
    }
    ;

init_declarator
    : declarator { printf("Reduction: init_declarator -> declarator\n"); }
    | declarator ASSIGN initializer { printf("Reduction: init_declarator -> declarator ASSIGN initializer\n"); }
    ;

type_specifier
    : VOID { printf("Reduction: type_specifier -> VOID\n"); }
    | CHAR { printf("Reduction: type_specifier -> CHAR\n"); }
    | INTEGER { printf("Reduction: type_specifier -> INTEGER\n"); }
    | FLOAT { printf("Reduction: type_specifier -> FLOAT\n"); }
    | BOOL { printf("Reduction: type_specifier -> BOOL\n"); }
    ;

declarator
    : pointer_opt direct_declarator { printf("Reduction: declarator -> pointer_opt direct_declarator\n"); }
    ;

pointer_opt
    : pointer { printf("Reduction: pointer_opt -> pointer\n"); }
    | /* empty */ { printf("Reduction: pointer_opt -> empty\n"); }
    ;

direct_declarator
    : IDENTIFIER {
        printf("Reduction: direct_declarator -> IDENTIFIER\n");
        addSymbol($1, "identifier", current_scope);
    }
    | IDENTIFIER '[' INTEGER_CONSTANT ']' {
        printf("Reduction: direct_declarator -> IDENTIFIER '[' INTEGER_CONSTANT ']'\n");
        addSymbol($1, "array", current_scope);
    }
    | IDENTIFIER LP parameter_list_opt RP {
        printf("Reduction: direct_declarator -> IDENTIFIER LP parameter_list_opt RP\n");
        addSymbol($1, "function", current_scope);
    }
    ;

pointer
    : ASTERISK { printf("Reduction: pointer -> ASTERISK\n"); }
    ;

parameter_list_opt
    : parameter_list { printf("Reduction: parameter_list_opt -> parameter_list\n"); }
    | /* empty */ { printf("Reduction: parameter_list_opt -> empty\n"); }
    ;

parameter_list
    : parameter_declaration { printf("Reduction: parameter_list -> parameter_declaration\n"); }
    | parameter_list COMMA parameter_declaration { printf("Reduction: parameter_list -> parameter_list COMMA parameter_declaration\n"); }
    ;

parameter_declaration
    : type_specifier pointer_opt IDENTIFIER {
        printf("Reduction: parameter_declaration -> type_specifier pointer_opt IDENTIFIER\n");
        addSymbol($3, "parameter", current_scope);
    }
    | type_specifier pointer_opt {
        printf("Reduction: parameter_declaration -> type_specifier pointer_opt\n");
    }
    ;

initializer
    : assignment_expression { printf("Reduction: initializer -> assignment_expression\n"); }
    ;

/* 3. Statements */
statement
    : compound_statement { printf("Reduction: statement -> compound_statement\n"); }
    | expression_statement { printf("Reduction: statement -> expression_statement\n"); }
    | selection_statement { printf("Reduction: statement -> selection_statement\n"); }
    | iteration_statement { printf("Reduction: statement -> iteration_statement\n"); }
    | jump_statement { printf("Reduction: statement -> jump_statement\n"); }
   /* | declaration */
    ;

compound_statement
    : MC_BEGIN { current_scope++; } block_item_list_opt END {
        printf("Reduction: compound_statement -> MC_BEGIN block_item_list_opt END\n");
        current_scope--;
    }
    ;

block_item_list_opt
    : block_item_list { printf("Reduction: block_item_list_opt -> block_item_list\n"); }
    | /* empty */ { printf("Reduction: block_item_list_opt -> empty\n"); }
    ;

block_item_list
    : block_item { printf("Reduction: block_item_list -> block_item\n"); }
    | block_item_list block_item { printf("Reduction: block_item_list -> block_item_list block_item\n"); }
    ;

block_item
    : declaration { printf("Reduction: block_item -> declaration\n"); }
    | statement { printf("Reduction: block_item -> statement\n"); }
    ;

expression_statement
    : expression_opt SEMICOLON { printf("Reduction: expression_statement -> expression_opt ';'\n"); }
    ;

expression_opt
    : expression { printf("Reduction: expression_opt -> expression\n"); }
    | /* empty */ { printf("Reduction: expression_opt -> empty\n"); }
    ;

selection_statement
    : IF LP expression RP statement {
        printf("Reduction: selection_statement -> IF LP expression RP statement\n");
    }
    | IF LP expression RP statement ELSE statement {
        printf("Reduction: selection_statement -> IF LP expression RP statement ELSE statement\n");
    }
    ;

iteration_statement
    : FOR LP expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RP statement {
        printf("Reduction: iteration_statement -> FOR LP expression_opt ';' expression_opt ';' expression_opt RP statement\n");
    }
    | FOR LP declaration expression_opt SEMICOLON expression_opt RP statement {
        printf("Reduction: iteration_statement -> FOR LP expression_opt ';' expression_opt ';' expression_opt RP statement\n");
    }
    ;

jump_statement
    : RETURN expression_opt SEMICOLON { printf("Reduction: jump_statement -> RETURN expression_opt ';'\n"); }
    ;

/* 4. Translation Unit */
translation_unit
    : function_definition { printf("Reduction: translation_unit -> function_definition\n"); }
    | declaration { printf("Reduction: translation_unit -> declaration\n"); }
    | expression { printf("Reduction: translation_unit -> expression\n"); }
    | translation_unit function_definition { printf("Reduction: translation_unit -> translation_unit function_definition\n"); }
    | translation_unit declaration { printf("Reduction: translation_unit -> translation_unit declaration\n"); }
    | statement
    | translation_unit statement
    | translation_unit expression
    ;

function_definition
    : type_specifier function_declarator compound_statement {
        printf("Reduction: function_definition -> type_specifier function_declarator compound_statement\n");
    }
  /*  | type_specifier declarator LP declaration_list_opt RP compound_statement {*/
    /*    printf("Reduction: function_definition -> type_specifier declarator LP declaration_list_opt RP compound_statement\n");*/
    /*}*/
    ;

function_declarator
    : pointer_opt IDENTIFIER LP parameter_list_opt RP {
        printf("Reduction: function_declarator -> pointer_opt IDENTIFIER LP parameter_list_opt RP\n");
        addSymbol($2, "function", current_scope);
    }
    ;

%%

/* Function to add symbol */
void addSymbol(char *name, char *type, int scope) {
    Symbol *s = (Symbol *)malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = strdup(type);
    s->scope = scope;
    s->next = symbolTable;
    symbolTable = s;
}

/* Function to find symbol */
Symbol *findSymbol(char *name, int scope) {
    Symbol *s = symbolTable;
    while (s) {
        if (strcmp(s->name, name) == 0 && s->scope == scope) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}

/* Function to print symbol table */
void printSymbolTable() {
    Symbol *s = symbolTable;
    printf("Symbol Table:\n");
    while (s) {
        printf("Name: %s, Type: %s, Scope: %d\n", s->name, s->type, s->scope);
        s = s->next;
    }
}

/* Error handling function */
void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

/* Main function */
int main() {
    printf("Parsing micro C code...\n");
    yyparse();
    printSymbolTable();
    return 0;
}
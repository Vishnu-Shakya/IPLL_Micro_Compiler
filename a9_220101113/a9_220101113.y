/* 
=========================== ATTRIBUTE DESIGN ===========================

→ Terminals:
- IDENTIFIER: 
    - Attributes: `sval` (name of identifier)
    - Used to look up symbol table entries.

- INT_CONST, FLOAT_CONST, CHAR_CONST, STRING_CONST:
    - Attributes: `ival`, `fval`, `cval`, `sval`
    - Used for constant folding and code generation.

→ Non-terminals:

1. expr:
    - Attributes:
        - place: Holds temporary name for the result.
        - type: Data type of the expression.
        - truelist / falselist: Used for boolean expressions in backpatching.
        - nextlist: For control flow tracking.
        - arrayFlag / ptrFlag: To distinguish between scalar, pointer, and array expressions.
        - isConstant: For constant folding.
        - value: Actual value if known.
    - Justification: Required for generating correct intermediate code and optimizations like folding.

2. stmt:
    - Attributes:
        - quad: Quad index used in backpatching.
        - nextlist: Control flow jump handling for statements.
    - Justification: Used in constructing control flow graphs and patching jump targets.

3. decl:
    - Attributes:
        - type: The data type of declaration.
        - size: Size of the data type.
        - isPtr / isArray: Flags for pointer or array declarations.
    - Justification: Helps in symbol table construction and memory allocation.

→ Inherited Attributes:
    - Inherited attributes are used in parameter and array dimension parsing,
      e.g., passing base types or scopes down during declaration parsing.

========================================================================
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quad.h"

// Function declarations
void yyerror(char *s);
int yylex(void);
void updateOffsets(SymbolTable *table);
char* getConstantValue(int ival, float fval, char cval, char *sval, int valueType);

// Global variables
SymbolEntry *currentFunctionEntry = NULL; // To keep track of current function during parsing
int currentOffset = 0;
int inLoop = 0;
QuadList *breakList = NULL;
QuadList *continueList = NULL;
%}

%union {
    int ival;
    float fval;
    char cval;
    char *sval;
    Type type;
    
    struct {
        char *place;         // Name of the result
        Type type;           // Type of expression
        QuadList *truelist;  // List of quads to patch for true condition
        QuadList *falselist; // List of quads to patch for false condition
        QuadList *nextlist;  // List of quads to patch for next statement
        int arrayFlag;       // Whether this is an array or not
        int ptrFlag;         // Whether this is a pointer or not

                // ✅ Add these:
        int isConstant;
        void *value;
    } expr;
    
    struct {
        int quad;           // Quad index for backpatching
        QuadList *nextlist; // Next list for statement
    } stmt;
    
    struct {
        Type type;          // Type of declaration
        int size;           // Size of variable
        int isPtr;          // Whether it's a pointer
        int isArray;        // Whether it's an array
        int arraySize;      // Size of array
        char *name;
    } decl;
    
    struct {
        int paramCount;     // Number of parameters
        char *name;         // Function name
    } func;
}

/* Token declarations */
%token <sval> IDENTIFIER
%token <ival> INTEGER_CONSTANT
%token <fval> FLOATING_CONSTANT
%token <cval> CHARACTER_CONSTANT
%token <sval> STRING_LITERAL

/* Keywords */
%token RETURN VOID <type> FLOAT <type> INTEGER <type> CHAR FOR CONST WHILE <type> BOOL IF DO ELSE MC_BEGIN END

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

/* Define types for non-terminals */
%type <expr> expression assignment_expression conditional_expression
%type <expr> logical_OR_expression logical_AND_expression equality_expression
%type <expr> relational_expression additive_expression multiplicative_expression
%type <expr> unary_expression postfix_expression primary_expression
%type <expr> expression_opt initializer argument_expression_list_opt argument_expression_list
%type <expr> unary_operator

%type <stmt> statement compound_statement expression_statement selection_statement func_statement
%type <stmt> iteration_statement jump_statement block_item block_item_list block_item_list_opt

%type <decl> declarator direct_declarator init_declarator pointer_opt pointer init_declarator_list
%type <type> type_specifier
%type <func> function_declarator parameter_list parameter_list_opt parameter_declaration

/* Marker for handling if-else */
%type <ival> M
%type <stmt> N

/* Define the starting non-terminal */
%start translation_unit

%%

/* Grammar rules with semantic actions */

/* Markers for backpatching */
M: /* empty */ { 
    $$ = nextquad(); 
};

N: /* empty */ {
    $<stmt>$.nextlist = makelist(nextquad());
    emitQuad("goto", NULL, NULL, "");
};

/* 1. Expressions */
expression
    : assignment_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    ;

assignment_expression
    : conditional_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | unary_expression ASSIGN assignment_expression {
        // Type checking
        if ($1.type != $3.type) {
            // Need type conversion
            if ($1.type == FLOAT_T && $3.type == INT_T) {
                $3.place = convInt2Float($3.place);
            } else if ($1.type == INT_T && $3.type == FLOAT_T) {
                $3.place = convFloat2Int($3.place);
            } else if ($1.type == INT_T && $3.type == CHAR_T) {
                $3.place = convChar2Int($3.place);
            } else if ($1.type == CHAR_T && $3.type == INT_T) {
                $3.place = convInt2Char($3.place);
            }
        }
        
        // Generate assignment quad
        if ($1.arrayFlag) {
            // Array assignment needs indexed copy
            emitQuad("[]=", $1.place, "", $3.place);
        } else if ($1.ptrFlag) {
            // Pointer assignment
            emitQuad("*=", $1.place, "", $3.place);
        } else {
            // Regular assignment
            emitQuad("=", $3.place, NULL, $1.place);
        }
        
        // Result of assignment is the left operand
        $$.place = $1.place;
        $$.type = $1.type;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    ;

conditional_expression
    : logical_OR_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | logical_OR_expression QUESTION_MARK M expression COLON M conditional_expression {
        // Create a temporary for result
        SymbolEntry *temp = gentemp(currentTable, typecheck($4.type, $7.type));
        
        // Backpatch the truelist of logical_OR_expression to the first M
        backpatch($1.truelist, $3);
        
        // Backpatch the falselist of logical_OR_expression to the second M
        backpatch($1.falselist, $6);
        
        // Generate quads for the assignments
        emitQuad("=", $4.place, NULL, temp->name);
        int quad1 = nextquad();
        emitQuad("goto", NULL, NULL, "");
        
        emitQuad("=", $7.place, NULL, temp->name);
        int quad2 = nextquad();
        
        // Backpatch the first goto to skip the second assignment
        char target[10];
        sprintf(target, "%d", quad2);
        quads[quad1].result = strdup(target);
        
        $$.place = temp->name;
        $$.type = temp->type;
        $$.truelist = NULL;
        $$.falselist = NULL;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    ;

logical_OR_expression
    : logical_AND_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | logical_OR_expression LOGICAL_OR M logical_AND_expression {
        // Backpatch the falselist of logical_OR_expression to the M
        backpatch($1.falselist, $3);
        
        // Result of logical OR is merged truelists
        $$.truelist = merge($1.truelist, $4.truelist);
        $$.falselist = $4.falselist;
        $$.type = BOOL_T;
        
        // If this is not a boolean expression, create a temporary
        if ($1.place && $4.place) {
            SymbolEntry *temp = gentemp(currentTable, INT_T);
            emitQuad("||", $1.place, $4.place, temp->name);
            $$.place = temp->name;
        }
    }
    ;

logical_AND_expression
    : equality_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | logical_AND_expression LOGICAL_AND M equality_expression {
        // Backpatch the truelist of logical_AND_expression to the M
        backpatch($1.truelist, $3);
        
        // Result of logical AND is merged falselists
        $$.falselist = merge($1.falselist, $4.falselist);
        $$.truelist = $4.truelist;
        $$.type = BOOL_T;
        
        // If this is not a boolean expression, create a temporary
        if ($1.place && $4.place) {
            SymbolEntry *temp = gentemp(currentTable, INT_T);
            emitQuad("&&", $1.place, $4.place, temp->name);
            $$.place = temp->name;
        }
    }
    ;

equality_expression
    : relational_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | equality_expression EQUAL_EQUAL relational_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, INT_T);
        
        // Generate quad for equality comparison
        emitQuad("==", $1.place, $3.place, temp->name);
        
        // For boolean expressions, create truelist and falselist
        $$.truelist = makelist(nextquad());
        emitQuad("if", temp->name, NULL, "");
        $$.falselist = makelist(nextquad());
        emitQuad("goto", NULL, NULL, "");
        
        $$.place = temp->name;
        $$.type = BOOL_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | equality_expression NOT_EQUAL relational_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, INT_T);
        
        // Generate quad for inequality comparison
        emitQuad("!=", $1.place, $3.place, temp->name);
        
        // For boolean expressions, create truelist and falselist
        $$.truelist = makelist(nextquad());
        emitQuad("if", temp->name, NULL, "");
        $$.falselist = makelist(nextquad());
        emitQuad("goto", NULL, NULL, "");
        
        $$.place = temp->name;
        $$.type = BOOL_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    ;

relational_expression
    : additive_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | relational_expression LESS_THAN additive_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, INT_T);
        
        // Generate quad for less than comparison
        emitQuad("<", $1.place, $3.place, temp->name);
        
        // For boolean expressions, create truelist and falselist
        $$.truelist = makelist(nextquad());
        emitQuad("if", temp->name, NULL, "");
        $$.falselist = makelist(nextquad());
        emitQuad("goto", NULL, NULL, "");
        
        $$.place = temp->name;
        $$.type = BOOL_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | relational_expression GREATER_THAN additive_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, INT_T);
        
        // Generate quad for greater than comparison
        emitQuad(">", $1.place, $3.place, temp->name);
        
        // For boolean expressions, create truelist and falselist
        $$.truelist = makelist(nextquad());
        emitQuad("if", temp->name, NULL, "");
        $$.falselist = makelist(nextquad());
        emitQuad("goto", NULL, NULL, "");
        
        $$.place = temp->name;
        $$.type = BOOL_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | relational_expression LESS_THAN_EQUAL additive_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, INT_T);
        
        // Generate quad for less than or equal comparison
        emitQuad("<=", $1.place, $3.place, temp->name);
        
        // For boolean expressions, create truelist and falselist
        $$.truelist = makelist(nextquad());
        emitQuad("if", temp->name, NULL, "");
        $$.falselist = makelist(nextquad());
        emitQuad("goto", NULL, NULL, "");
        
        $$.place = temp->name;
        $$.type = BOOL_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | relational_expression GREATER_THAN_EQUAL additive_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, INT_T);
        
        // Generate quad for greater than or equal comparison
        emitQuad(">=", $1.place, $3.place, temp->name);
        
        // For boolean expressions, create truelist and falselist
        $$.truelist = makelist(nextquad());
        emitQuad("if", temp->name, NULL, "");
        $$.falselist = makelist(nextquad());
        emitQuad("goto", NULL, NULL, "");
        
        $$.place = temp->name;
        $$.type = BOOL_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    ;

additive_expression
    : multiplicative_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | additive_expression PLUS multiplicative_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, resultType);
        
        // Generate quad for addition
        emitQuad("+", $1.place, $3.place, temp->name);
        
        $$.place = temp->name;
        $$.type = resultType;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | additive_expression MINUS multiplicative_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, resultType);
        
        // Generate quad for subtraction
        emitQuad("-", $1.place, $3.place, temp->name);
        
        $$.place = temp->name;
        $$.type = resultType;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    ;

multiplicative_expression
    : unary_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | multiplicative_expression ASTERISK unary_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, resultType);
        
        // Generate quad for multiplication
        emitQuad("*", $1.place, $3.place, temp->name);
        
        $$.place = temp->name;
        $$.type = resultType;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | multiplicative_expression FORWARD_SLASH unary_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, resultType);
        
        // Generate quad for division
        emitQuad("/", $1.place, $3.place, temp->name);
        
        $$.place = temp->name;
        $$.type = resultType;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | multiplicative_expression PERCENT unary_expression {
        Type resultType = typecheck($1.type, $3.type);
        
        // Create temporary for result
        SymbolEntry *temp = gentemp(currentTable, resultType);
        
        // Generate quad for modulo
        emitQuad("%", $1.place, $3.place, temp->name);
        
        $$.place = temp->name;
        $$.type = resultType;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    ;

unary_operator
    : AMPERSAND {
        $$.type = PTR_T;
        $$.place = "address";
    }
    | ASTERISK {
        $$.type = PTR_T;
        $$.place = "deref";
    }
    | PLUS {
        $$.type = INT_T;
        $$.place = "uplus";
    }
    | MINUS {
        $$.type = INT_T;
        $$.place = "uminus";
    }
    | EXCLAMATION {
        $$.type = BOOL_T;
        $$.place = "not";
    }
    ;

unary_expression
    : postfix_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | unary_operator unary_expression {
        if (strcmp($1.place, "address") == 0) {
            // Address operator
            SymbolEntry *temp = gentemp(currentTable, PTR_T);
            emitQuad("&", $2.place, NULL, temp->name);
            $$.place = temp->name;
            $$.type = PTR_T;
            $$.ptrFlag = 1;
        } else if (strcmp($1.place, "deref") == 0) {
            // Dereference operator
            SymbolEntry *temp = gentemp(currentTable, INT_T); // Assuming int for now
            emitQuad("*", $2.place, NULL, temp->name);
            $$.place = temp->name;
            $$.type = INT_T;
            $$.ptrFlag = 0;
        } else if (strcmp($1.place, "uminus") == 0) {
            // Unary minus
            SymbolEntry *temp = gentemp(currentTable, $2.type);
            emitQuad("uminus", $2.place, NULL, temp->name);
            $$.place = temp->name;
            $$.type = $2.type;
        } else if (strcmp($1.place, "not") == 0) {
            // Logical not
            $$.truelist = $2.falselist;
            $$.falselist = $2.truelist;
            $$.type = BOOL_T;
            
            // If not already a boolean expression
            if (!$2.truelist && !$2.falselist) {
                SymbolEntry *temp = gentemp(currentTable, INT_T);
                emitQuad("!", $2.place, NULL, temp->name);
                $$.place = temp->name;
                $$.truelist = makelist(nextquad());
                emitQuad("if", temp->name, NULL, "");
                $$.falselist = makelist(nextquad());
                emitQuad("goto", NULL, NULL, "");
            } else {
                $$.place = NULL;
            }
        } else {
            // Unary plus (no operation needed)
            $$.place = $2.place;
            $$.type = $2.type;
        }
        
        $$.arrayFlag = 0;
    }
    | INCREMENT unary_expression {
        // Generate temporary for the original value
        SymbolEntry *temp = gentemp(currentTable, $2.type);
        
        // Save the original value
        emitQuad("=", $2.place, NULL, temp->name);
        
        // Increment the value
        emitQuad("+", $2.place, "1", $2.place);
        
        // Result is the original value
        $$.place = temp->name;
        $$.type = $2.type;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | DECREMENT unary_expression {
        // Generate temporary for the original value
        SymbolEntry *temp = gentemp(currentTable, $2.type);
        
        // Save the original value
        emitQuad("=", $2.place, NULL, temp->name);
        
        // Decrement the value
        emitQuad("-", $2.place, "1", $2.place);
        
        // Result is the original value
        $$.place = temp->name;
        $$.type = $2.type;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | postfix_expression INCREMENT {
        // Generate temporary for the original value
        SymbolEntry *temp = gentemp(currentTable, $1.type);
        
        // Save the original value
        emitQuad("=", $1.place, NULL, temp->name);
        
        // Increment the value
        emitQuad("+", $1.place, "1", $1.place);
        
        // Result is the original value
        $$.place = temp->name;
        $$.type = $1.type;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    | postfix_expression DECREMENT {
        // Generate temporary for the original value
        SymbolEntry *temp = gentemp(currentTable, $1.type);
        
        // Save the original value
        emitQuad("=", $1.place, NULL, temp->name);
        
        // Decrement the value
        emitQuad("-", $1.place, "1", $1.place);
        
        // Result is the original value
        $$.place = temp->name;
        $$.type = $1.type;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    ;

argument_expression_list_opt
    : argument_expression_list {
        $$.place = $1.place;
        $$.type = $1.type;
    }
    | /* empty */ {
        $$.place = NULL;
        $$.type = VOID_T;
    }
    ;

argument_expression_list
    : assignment_expression {
        // Generate quad for parameter
        emitQuad("param", $1.place, NULL, NULL);
        
        $$.place = $1.place;
        $$.type = $1.type;
    }
    | argument_expression_list COMMA assignment_expression {
        // Generate quad for parameter
        emitQuad("param", $3.place, NULL, NULL);
        
        $$.place = $1.place;
        $$.type = $1.type;
    }
    ;

postfix_expression
    : primary_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
        $$.arrayFlag = $1.arrayFlag;
        $$.ptrFlag = $1.ptrFlag;
    }
    | postfix_expression '[' expression ']' {
        // Handling array access
        SymbolEntry *temp = gentemp(currentTable, INT_T);
        
        // Calculate offset (expression * size of element)
        SymbolEntry *size = gentemp(currentTable, INT_T);
        char sizeStr[10];
        sprintf(sizeStr, "%d", sizeOfType(INT_T)); // Assuming INT_T elements
        emitQuad("=", sizeStr, NULL, size->name);
        
        emitQuad("*", $3.place, size->name, temp->name);
        
        // Get the value from array
        SymbolEntry *value = gentemp(currentTable, INT_T);
        emitQuad("=[]", $1.place, temp->name, value->name);
        
        $$.place = value->name;
        $$.type = INT_T;
        $$.arrayFlag = 1;
        $$.ptrFlag = 0;
    }
    | postfix_expression LP argument_expression_list_opt RP {
        // Function call
        // Create a temporary for the return value
        SymbolEntry *temp = gentemp(currentTable, INT_T); // Assuming int return type
        
        // Generate quad for function call
        char paramCount[10];
        sprintf(paramCount, "%d", 0); // Number of parameters
        emitQuad("call", $1.place, paramCount, temp->name);
        
        $$.place = temp->name;
        $$.type = INT_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
    }
    ;

primary_expression
    : IDENTIFIER {
        // Look up identifier in symbol table
        SymbolEntry *entry = lookup(currentTable, $1);
        if (!entry) {
            // If not found, create a new entry
            entry = insert(currentTable, $1, INT_T); // Assuming int by default
        }
        
        $$.place = entry->name;
        $$.type = entry->type;
        $$.arrayFlag = (entry->type == ARRAY_T);
        $$.ptrFlag = (entry->type == PTR_T);
        $$.truelist = NULL;
        $$.falselist = NULL;
    }
    | INTEGER_CONSTANT {
        // Create a temporary for the constant
        SymbolEntry *temp = gentemp(currentTable, INT_T);
        
        // Convert integer to string
        char valueStr[20];
        sprintf(valueStr, "%d", $1);
        
        // Assign the constant value
        emitQuad("=", valueStr, NULL, temp->name);
        
        $$.place = temp->name;
        $$.type = INT_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
        $$.truelist = NULL;
        $$.falselist = NULL;

        $$.isConstant = 1;
        int *val = (int*)malloc(sizeof(int));
        *val = $1;
        $$.value = val;
    }
    | FLOATING_CONSTANT {
        // Create a temporary for the constant
        SymbolEntry *temp = gentemp(currentTable, FLOAT_T);
        
        // Convert float to string
        char valueStr[20];
        sprintf(valueStr, "%f", $1);
        
        // Assign the constant value
        emitQuad("=", valueStr, NULL, temp->name);
        
        $$.place = temp->name;
        $$.type = FLOAT_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
        $$.truelist = NULL;
        $$.falselist = NULL;

        $$.isConstant = 1;
        float *val = (float *)malloc(sizeof(float));
        *val = $1;
        $$.value = val;
    }
    | CHARACTER_CONSTANT {
        // Create a temporary for the constant
        SymbolEntry *temp = gentemp(currentTable, CHAR_T);
        
        // Convert character to string
        char valueStr[20];
        sprintf(valueStr, "%d", (int)$1);
        
        // Assign the constant value
        emitQuad("=", valueStr, NULL, temp->name);
        
        $$.place = temp->name;
        $$.type = CHAR_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 0;
        $$.truelist = NULL;
        $$.falselist = NULL;
        $$.isConstant = 1;

        char *val = (char *)malloc(sizeof(char));
        *val = $1;
        $$.value = val;
    }
    | STRING_LITERAL {
        // Create a temporary for the string literal
        SymbolEntry *temp = gentemp(currentTable, PTR_T);
        
        // Assign the string literal
        emitQuad("=", $1, NULL, temp->name);
        
        $$.place = temp->name;
        $$.type = PTR_T;
        $$.arrayFlag = 0;
        $$.ptrFlag = 1;
        $$.truelist = NULL;
        $$.falselist = NULL;
        
    }
    | LP expression RP {
        $$.place = $2.place;
        $$.type = $2.type;
        $$.truelist = $2.truelist;
        $$.falselist = $2.falselist;
        $$.arrayFlag = $2.arrayFlag;
        $$.ptrFlag = $2.ptrFlag;
    }
    ;

/* 2. Declarations */
declaration
    : type_specifier init_declarator_list SEMICOLON {
        // Update the type of the declared variable
        SymbolEntry *entry = lookup(currentTable, $2.name);
        if (entry) {
            updateSymbolType(entry, $1);
            
            // Update size based on type
            updateSymbolSize(entry, sizeOfType($1));
            
            // For arrays, multiply by array size
            if ($2.isArray) {
                updateSymbolSize(entry, sizeOfType($1) * $2.arraySize);
                updateSymbolType(entry, ARRAY_T);
                updateSymbolArraySize(entry, $2.arraySize);
                updateSymbolElementType(entry, $1);
            }
            
            // For pointers
            if ($2.isPtr) {
                updateSymbolType(entry, PTR_T);
                updateSymbolElementType(entry, $1);
            }
        }
    }
    ;
init_declarator_list
    : init_declarator
    {
        // No additional action needed for single declarator
    }
    | init_declarator_list COMMA init_declarator
    {
        // The actions for each declarator are already handled in init_declarator
    }
    ;

init_declarator
    : declarator {

        // Update offset for the variable
        // SymbolEntry *entry = lookup(currentTable, $1.name);
        // if (entry) {
        //     updateSymbolOffset(entry, currentOffset);
        //     currentOffset += entry->size;
        // }
         // ✅ Insert variable into current scope
        SymbolEntry *entry = insert(currentTable, $1.name, $1.type);
        //SymbolEntry *entry = lookup(currentTable, $1.name);

        if (entry) {
                updateSymbolOffset(entry, currentOffset);
                updateSymbolSize(entry, sizeOfType($1.type));  // base type size
                currentOffset += entry->size;

                if ($1.isArray) {
                    updateSymbolType(entry, ARRAY_T);                       // mark as array
                    updateSymbolArraySize(entry, $1.arraySize);             // save array length
                    updateSymbolElementType(entry, $1.type);                // what type it stores

                    int fullSize = sizeOfType($1.type) * $1.arraySize;
                    updateSymbolSize(entry, fullSize);                      // ✅ set full size
                    currentOffset += fullSize-sizeOfType($1.type); // update offset
                }

            if ($1.isPtr) {
                updateSymbolType(entry, PTR_T);
                updateSymbolElementType(entry, $1.type);
            }

        }

        $$.type = $1.type;
        $$.size = $1.size;
        $$.isPtr = $1.isPtr;
        $$.isArray = $1.isArray;
        $$.arraySize = $1.arraySize;
        $$.name = $1.name;
    }
    | declarator ASSIGN initializer {

        // Update offset for the variable
        // SymbolEntry *entry = lookup(currentTable, $1.name);
        // if (entry) {
        //     updateSymbolOffset(entry, currentOffset);
        //     currentOffset += entry->size;
        // }

        // // Generate assignment quad
        // emitQuad("=", $3.place, NULL, $1.name);
                // ✅ Insert variable into current scope
        SymbolEntry *entry = insert(currentTable, $1.name, $1.type);

        if (entry) {
            updateSymbolOffset(entry, currentOffset);
            updateSymbolSize(entry, sizeOfType($1.type));
            currentOffset += entry->size;

            if ($1.isArray) {
                updateSymbolSize(entry, entry->size * $1.arraySize);
                updateSymbolType(entry, ARRAY_T);
                updateSymbolArraySize(entry, $1.arraySize);
                updateSymbolElementType(entry, $1.type);
            }

            if ($1.isPtr) {
                updateSymbolType(entry, PTR_T);
                updateSymbolElementType(entry, $1.type);
            }

            // ✅ Generate assignment quad
            emitQuad("=", $3.place, NULL, $1.name);

             // ✅ Store the constant value if it's known
            if ($3.isConstant) {
            updateSymbolInitialValue(entry, $3.value);
           }
        }
        
        $$.type = $1.type;
        $$.size = $1.size;
        $$.isPtr = $1.isPtr;
        $$.isArray = $1.isArray;
        $$.arraySize = $1.arraySize;
        $$.name = $1.name;
    }
    ;

type_specifier
    : VOID { $$ = VOID_T; }
    | CHAR { $$ = CHAR_T; }
    | INTEGER { $$ = INT_T; }
    | FLOAT { $$ = FLOAT_T; }
    | BOOL { $$ = BOOL_T; }
    ;

declarator
    : pointer_opt direct_declarator {
        $$.type = $2.type;
        $$.size = $2.size;
        $$.isPtr = $1.isPtr;
        $$.isArray = $2.isArray;
        $$.arraySize = $2.arraySize;
        $$.name = $2.name;
    }
    ;

pointer_opt
    : pointer {
        $$.isPtr = 1;
        $$.type = PTR_T;
        $$.size = sizeOfType(PTR_T);
    }
    | /* empty */ {
        $$.isPtr = 0;
        $$.type = INT_T; // Default type
        $$.size = 0;
    }
    ;

direct_declarator
    : IDENTIFIER {
        // Add identifier to symbol table
        SymbolEntry *entry = insert(currentTable, $1, INT_T); // Default type, will be updated later
        
        $$.name = entry->name;
        $$.type = entry->type;
        $$.size = entry->size;
        $$.isArray = 0;
        $$.arraySize = 0;
    }
    | IDENTIFIER '[' INTEGER_CONSTANT ']' {
        // Add array to symbol table
        SymbolEntry *entry = insert(currentTable, $1, ARRAY_T);
        updateSymbolArraySize(entry, $3); // Assuming int elements
        updateSymbolElementType(entry, INT_T); // Default element type
        
        $$.name = entry->name;
        $$.type = entry->type;
        $$.size = entry->size;
        $$.isArray = 1;
        $$.arraySize = $3;
    }
    | IDENTIFIER LP parameter_list_opt RP {
        // Function declaration
        // Create a new symbol table for the function
        SymbolTable *functionTable = createSymbolTable($1, currentTable);
        
        // Add function to current table
        SymbolEntry *entry = insert(currentTable, $1, FUNC_T);
        entry->nestedTable = functionTable;
        
        $$.name = entry->name;
        $$.type = entry->type;
        $$.size = 0;
        $$.isArray = 0;
        $$.arraySize = 0;
    }
    ;

pointer
    : ASTERISK {
        $$.isPtr = 1;
        $$.type = PTR_T;
        $$.size = sizeOfType(PTR_T);
    }
    ;

parameter_list_opt
    : parameter_list {
        $$.paramCount = $1.paramCount;
        $$.name = $1.name;
    }
    | /* empty */ {
        $$.paramCount = 0;
        $$.name = NULL;
    }
    ;

parameter_list
    : parameter_declaration {
        $$.paramCount = 1;
        $$.name = $1.name;
    }
    | parameter_list COMMA parameter_declaration {
        $$.paramCount = $1.paramCount + 1;
        $$.name = $1.name;
    }
    ;

parameter_declaration
    : type_specifier pointer_opt IDENTIFIER {
        // Add parameter to current function's symbol table
       // SymbolEntry *entry = insert(currentTable, $3, $1);

       // Make sure we're adding to the function's symbol table, not current context
        SymbolTable *targetTable = currentFunctionEntry ? currentFunctionEntry->nestedTable : currentTable;
        
        // Add parameter to function's symbol table
        SymbolEntry *entry = insert(targetTable, $3, $1);

      //  printf(">> Inserting param '%s' into scope: %s\n", $3, currentTable->name);

        
        if ($2.isPtr) {
            updateSymbolType(entry, PTR_T);
            updateSymbolElementType(entry, $1);
        }
        
        updateSymbolOffset(entry, currentOffset);
        currentOffset += entry->size;
        
        $$.name = entry->name;
       // $$.type = $1;
        
    }
    | type_specifier pointer_opt {
        $$.name = NULL;
         //$$.type = $1;
        
    }
    ;

initializer
    : assignment_expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.isConstant = $1.isConstant;  // Must be set somewhere in expr rules
        $$.value = $1.value;            // Store raw constant value
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
    }
    ;

/* 3. Statements */
statement
    : compound_statement {
        $$.nextlist = $1.nextlist;
    }
    | expression_statement {
        $$.nextlist = $1.nextlist;
    }
    | func_statement {
        $$.nextlist = $1.nextlist;
    }
    | selection_statement {
        $$.nextlist = $1.nextlist;
    }
    | iteration_statement {
        $$.nextlist = $1.nextlist;
    }
    | jump_statement {
        $$.nextlist = $1.nextlist;
    }
    ;

compound_statement
    : MC_BEGIN {
        // Push a new symbol table for this block
        //char blockName[20];
       // sprintf(blockName, "Block_%d", nextquad());
        // SymbolTable *blockTable = createSymbolTable(blockName, currentTable);
        // currentTable = blockTable;
        
    } block_item_list_opt END {
        // Restore parent symbol table
       // currentTable = currentTable->parent;
        
        // Propagate nextlist only if block_item_list_opt is present
        if ($3.nextlist) {
            $$.nextlist = $3.nextlist;
        } else {
            $$.nextlist = NULL;
        }
    }
    ;

func_statement
    : MC_BEGIN {
        // Push a new symbol table for this block
        //char blockName[20];
       // sprintf(blockName, "Block_%d", nextquad());
        // SymbolTable *blockTable = createSymbolTable(blockName, currentTable);
        // currentTable = blockTable;
        
    } block_item_list_opt END {
        // Restore parent symbol table
        currentTable = currentTable->parent;
        
        // Propagate nextlist only if block_item_list_opt is present
        if ($3.nextlist) {
            $$.nextlist = $3.nextlist;
        } else {
            $$.nextlist = NULL;
        }
    }
    ;

block_item_list_opt
    : block_item_list {
        $$.nextlist = $1.nextlist;
    }
    | /* empty */ {
        $$.nextlist = NULL;
    }
    ;

block_item_list
    : block_item {
        $$.nextlist = $1.nextlist;
    }
    | block_item_list M block_item {
        // Backpatch the end of the previous block item
        backpatch($1.nextlist, $2);
        
        // The nextlist of the whole block is the nextlist of the last item
        $$.nextlist = $3.nextlist;
    }
    ;

block_item
    : declaration {
        $$.nextlist = NULL;
    }
    | statement {
        $$.nextlist = $1.nextlist;
    }
    ;

expression_statement
    : expression_opt SEMICOLON {
        $$.nextlist = $1.nextlist;
    }
    ;

expression_opt
    : expression {
        $$.place = $1.place;
        $$.type = $1.type;
        $$.truelist = $1.truelist;
        $$.falselist = $1.falselist;
         $$.nextlist = NULL;
        //$$.nextlist=$1.nextlist;
    }
    | /* empty */ {
        $$.place = NULL;
        $$.truelist = NULL;
        $$.falselist = NULL;
        $$.nextlist = NULL;
    }
    ;

selection_statement
    : IF LP expression RP M statement {
        // Backpatch the truelist of the expression to the beginning of the statement
        backpatch($3.truelist, $5);
        
        // The nextlist is the merge of the falselist and the nextlist of the statement
        $$.nextlist = merge($3.falselist, $6.nextlist);
    }
    | IF LP expression RP M statement ELSE N M statement {
        // Backpatch the truelist of the expression to the first statement
        backpatch($3.truelist, $5);
        
        // Backpatch the falselist of the expression to the second statement
        backpatch($3.falselist, $9);
        
        // The nextlist is the merge of the nextlists of both statements and the goto after first statement
        $$.nextlist = merge(merge($6.nextlist, $8.nextlist), $10.nextlist);
    }
    ;

iteration_statement
    : FOR LP expression_opt SEMICOLON M expression_opt SEMICOLON M expression_opt RP M statement {
        // This is for loop: for(expr1; expr2; expr3) stmt
        
        // Save old loop info
        QuadList *oldBreak = breakList;
        QuadList *oldContinue = continueList;
        int oldInLoop = inLoop;
        
        // Set new loop info
        inLoop = 1;
        breakList = NULL;
        continueList = NULL;
        
        // Backpatch the truelist of expr2 to the beginning of the statement
        backpatch($6.truelist, $11);
        
        // Backpatch the nextlist of the statement to the beginning of expr3
        backpatch($12.nextlist, $8);
        
        // Generate a jump back to the evaluation of expr2
        char labelStr[10];
        sprintf(labelStr, "%d", $5);
        emitQuad("goto", NULL, NULL, labelStr);
        
        // The nextlist is the falselist of expr2
        $$.nextlist = merge($6.falselist, breakList);
        
        // Backpatch continue statements to the beginning of expr3
        backpatch(continueList, $8);
        
        // Restore old loop info
        inLoop = oldInLoop;
        breakList = oldBreak;
        continueList = oldContinue;
    }
    | WHILE M LP expression RP M statement {
        // Save old loop info
        QuadList *oldBreak = breakList;
        QuadList *oldContinue = continueList;
        int oldInLoop = inLoop;
        
        // Set new loop info
        inLoop = 1;
        breakList = NULL;
        continueList = NULL;
        
        // Backpatch the truelist of the expression to the beginning of the statement
        backpatch($4.truelist, $6);
        
        // Backpatch the nextlist of the statement to the beginning of the expression
        backpatch($7.nextlist, $2);
        
        // Backpatch continue statements to the beginning of the expression
        backpatch(continueList, $2);
        
        // Generate a jump back to the expression
        char labelStr[10];
        sprintf(labelStr, "%d", $2);
        emitQuad("goto", NULL, NULL, labelStr);
        
        // The nextlist is the falselist of the expression merged with break statements
        $$.nextlist = merge($4.falselist, breakList);
        
        // Restore old loop info
        inLoop = oldInLoop;
        breakList = oldBreak;
        continueList = oldContinue;
    }
    | DO M statement WHILE M LP expression RP SEMICOLON {
        // Save old loop info
        QuadList *oldBreak = breakList;
        QuadList *oldContinue = continueList;
        int oldInLoop = inLoop;
        
        // Set new loop info
        inLoop = 1;
        breakList = NULL;
        continueList = NULL;
        
        // Backpatch the nextlist of the statement to the beginning of the expression
        backpatch($3.nextlist, $5);
        
        // Backpatch continue statements to the beginning of the expression
        backpatch(continueList, $5);
        
        // Backpatch the truelist of the expression to the beginning of the statement
        backpatch($7.truelist, $2);
        
        // The nextlist is the falselist of the expression merged with break statements
        $$.nextlist = merge($7.falselist, breakList);
        
        // Restore old loop info
        inLoop = oldInLoop;
        breakList = oldBreak;
        continueList = oldContinue;
    }
    ;

jump_statement
    : RETURN expression_opt SEMICOLON {
        // Generate return statement
        if ($2.place) {
            emitQuad("return", $2.place, NULL, NULL);
        } else {
            emitQuad("return", NULL, NULL, NULL);
        }
        
        $$.nextlist = NULL;
    }
    ;

/* 4. Translation Unit */
translation_unit
    : function_definition { /* No action needed */ }
    | declaration { /* No action needed */ }
    | expression { /* No action needed */ }
    | translation_unit function_definition { /* No action needed */ }
    | translation_unit declaration { /* No action needed */ }
    | statement { /* No action needed */ }
    | translation_unit statement { /* No action needed */ }
    | translation_unit expression { /* No action needed */ }
    ;

function_definition
    : type_specifier function_declarator {
        // Switch currentTable to function's scope
        // SymbolEntry *funcEntry = currentFunctionEntry;
        SymbolEntry *funcEntry = lookup(globalTable, $2.name);
        if (funcEntry && funcEntry->nestedTable) {
            currentTable = funcEntry->nestedTable;
            currentOffset = 0;

            // Add return value entry
            SymbolEntry *retVal = insert(currentTable, "retVal", $1);
            updateSymbolOffset(retVal, currentOffset);
            currentOffset += retVal->size;

            // Emit function start
            emitQuad("func_begin", funcEntry->name, NULL, NULL);
        }
    } func_statement {
        // Emit function end
        emitQuad("func_end", NULL, NULL, NULL);

        // Restore global context
        currentTable = globalTable;
        currentFunctionEntry = NULL;
        currentOffset = 0;
    };


function_declarator
    : pointer_opt IDENTIFIER LP parameter_list_opt RP {
        // Insert function into global symbol table
        SymbolEntry *entry = lookup(currentTable, $2);
        if (!entry) {
            entry = insert(currentTable, $2, FUNC_T);
        }

        // Create a nested table for the function
        //SymbolTable *funcTable = createSymbolTable($2, currentTable);
        //entry->nestedTable = funcTable;

         // Create a nested table for the function if it doesn't exist
        if (!entry->nestedTable) {
            SymbolTable *funcTable = createSymbolTable($2, currentTable);
            entry->nestedTable = funcTable;
        }

        // Store parameter count in function entry
        entry->paramCount = $4.paramCount;

        // Set function context for use in function_definition
        $$.name = entry->name;
        $$.paramCount = $4.paramCount;

        // 💡 Save function table pointer for function_definition
        currentFunctionEntry = entry;
    };


%%

/* Error handling function */
void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

/* Main function */
int main() {
    // Initialize global symbol table
    globalTable = createSymbolTable("global", NULL);
    currentTable = globalTable;
    
    // Initialize quad array (if needed)
    // Note: quad.c doesn't show an initQuads() function, 
    // so we'll assume quadIndex = 0 is sufficient initialization
    quadIndex = 0;
    
    // Parse input
    yyparse();
    
    printQuads();

    printQuadsinstruction();
    // Print results
    printSymbolTable(globalTable);

        // Print all nested symbol tables
    SymbolEntry *entry = globalTable->entries;
    while (entry) {
        if (entry->nestedTable) {
            printSymbolTable(entry->nestedTable);
        }
        entry = entry->next;
    }
    // printQuads();
    
    return 0;
}
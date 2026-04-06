#ifndef QUAD_H
#define QUAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type definition for type checking and conversions
typedef enum Type {
    VOID_T,
    CHAR_T,
    INT_T,
    FLOAT_T,
    PTR_T,
    ARRAY_T,
    FUNC_T,
    BOOL_T  // Implicit type for logical operations
} Type;

// Symbol table entry structure
typedef struct SymbolEntry {
    char *name;           // Name of the symbol
    Type type;            // Type of the symbol
    Type eleType;         // Element type for arrays and pointer targets
    int size;             // Size of the symbol in bytes
    int offset;           // Offset in memory
    int arraySize;        // Size of array (if applicable)
    void *initialValue;   // Initial value (if any)
    struct SymbolTable *nestedTable; // Nested symbol table (for functions)
    struct SymbolEntry *next;  // Next entry in the table
    int paramCount;
} SymbolEntry;

// Symbol table structure
typedef struct SymbolTable {
    char *name;          // Name of the table (function name or "global")
    int tempCount;       // Counter for temporaries
    struct SymbolEntry *entries; // Entries in the table
    struct SymbolTable *parent;  // Parent table (for nested scopes)
} SymbolTable;

// Expression attributes structure
typedef struct ExprAttr {
    SymbolEntry *place;    // Symbol table entry for result of expression
    Type type;             // Type of expression
    int truelist;          // List of quads to patch for true condition
    int falselist;         // List of quads to patch for false condition
    int nextlist;          // List of quads to patch for next statement
    int arrayOffset;       // Offset for array access
    int isLValue;          // Whether this is an lvalue (can be on left side of assignment)
    int isArray;           // Whether this is an array
    int isPtr;             // Whether this is a pointer
} ExprAttr;

// Quad structure (for 3-address code)
typedef struct Quad {
    char *op;              // Operator
    char *arg1;            // Argument 1
    char *arg2;            // Argument 2
    char *result;          // Result
} Quad;

// List structure for backpatching
typedef struct QuadList {
    int index;             // Index of quad
    struct QuadList *next; // Next list item
} QuadList;

// Function declarations for symbol table
SymbolTable* createSymbolTable(char *name, SymbolTable *parent);
SymbolEntry* lookup(SymbolTable *table, char *name);
SymbolEntry* lookupInCurrentScope(SymbolTable *table, char *name);
SymbolEntry* insert(SymbolTable *table, char *name, Type type);
SymbolEntry* gentemp(SymbolTable *table, Type type);
void updateSymbolType(SymbolEntry *entry, Type type);
void updateSymbolSize(SymbolEntry *entry, int size);
void updateSymbolOffset(SymbolEntry *entry, int offset);
void updateSymbolInitialValue(SymbolEntry *entry, void *value);
void updateSymbolArraySize(SymbolEntry *entry, int size);
void updateSymbolElementType(SymbolEntry *entry, Type type);
void printSymbolTable(SymbolTable *table);

// Function declarations for quads
void emitQuad(char *op, char *arg1, char *arg2, char *result);
void printQuads();
int nextquad();
QuadList* makelist(int i);
QuadList* merge(QuadList *p1, QuadList *p2);
void backpatch(QuadList *p, int i);

// Type conversion functions
Type typecheck(Type type1, Type type2);
char* convInt2Float(char *s);
char* convFloat2Int(char *s);
char* convChar2Int(char *s);
char* convInt2Char(char *s);
char* convBool2Int(char *s);
char* convInt2Bool(char *s);

// Global variables
extern SymbolTable *currentTable;
extern SymbolTable *globalTable;
extern Quad quads[1000];  // Assuming a maximum of 1000 quads
extern int quadIndex;
extern int tempVarCount;
extern int labelCount;

// Helper functions
char* newLabel();
char* newTemp();
int sizeOfType(Type type);
char* typeToString(Type type);

#endif
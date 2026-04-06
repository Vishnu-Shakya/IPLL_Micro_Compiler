#include "quad.h"

// Global variables
SymbolTable *currentTable = NULL;
SymbolTable *globalTable = NULL;
Quad quads[1000];  // Array to store quads
int quadIndex = 0;
int tempVarCount = 0;
int labelCount = 0;

// Symbol table functions
SymbolTable* createSymbolTable(char *name, SymbolTable *parent) {
    SymbolTable *table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->name = strdup(name);
    table->tempCount = 0;
    table->entries = NULL;
    table->parent = parent;
    return table;
}

SymbolEntry* lookup(SymbolTable *table, char *name) {
    // First search in current scope
    SymbolEntry *entry = lookupInCurrentScope(table, name);
    if (entry) return entry;
    
    // If not found and there's a parent scope, search there
    if (table->parent) 
        return lookup(table->parent, name);
    
    return NULL;
}

SymbolEntry* lookupInCurrentScope(SymbolTable *table, char *name) {
    SymbolEntry *entry = table->entries;
    while (entry) {
        if (strcmp(entry->name, name) == 0)
            return entry;
        entry = entry->next;
    }
    return NULL;
}

SymbolEntry* insert(SymbolTable *table, char *name, Type type) {
    // Check if already exists in current scope
    SymbolEntry *existingEntry = lookupInCurrentScope(table, name);
    if (existingEntry) {
        return existingEntry; // Symbol already exists
    }
    
    // Create new entry
    SymbolEntry *entry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    entry->name = strdup(name);
    entry->type = type;
    entry->eleType = VOID_T;
    entry->size = sizeOfType(type);
    entry->offset = 0;  // Will be updated later
    entry->arraySize = 0;
    entry->initialValue = NULL;
    entry->nestedTable = NULL;
    entry->paramCount = 0;
        // Compute offset
        int cumulativeOffset = 0;
        SymbolEntry *temp = table->entries;
       // SymbolEntry *prev = temp;
        while (temp) {
            cumulativeOffset += temp->size;
         //   prev=temp;
            temp = temp->next;
        }
        entry->offset = cumulativeOffset;
     //if(table->entries==NULL){
        entry->next = table->entries;
        table->entries = entry;
     //}else{
    // Add to the beginning of the list
    //prev->next = entry;
    // }
    // table->entries = entry;
    
    return entry;
}

SymbolEntry* gentemp(SymbolTable *table, Type type) {
    // Generate a unique temporary name
    char tempName[20];
    sprintf(tempName, "t%d", table->tempCount++);
    
    // Insert into symbol table
    SymbolEntry *entry = insert(table, tempName, type);
    
    return entry;
}

void updateSymbolType(SymbolEntry *entry, Type type) {
    entry->type = type;
    entry->size = sizeOfType(type);
}

void updateSymbolSize(SymbolEntry *entry, int size) {
    entry->size = size;
}

void updateSymbolOffset(SymbolEntry *entry, int offset) {
    entry->offset = offset;
}

void updateSymbolInitialValue(SymbolEntry *entry, void *value) {
    entry->initialValue = value;
}

void updateSymbolArraySize(SymbolEntry *entry, int size) {
    entry->arraySize = size;
}

void updateSymbolElementType(SymbolEntry *entry, Type type) {
    entry->eleType = type;
}

// void printSymbolTable(SymbolTable *table) {
//     printf("\nSymbol Table: %s\n", table->name);
//     printf("Name\tType\tElementType\tSize\tOffset\tInitialValue\n");
//     printf("-----------------------------------------------------\n");
    
//     SymbolEntry *entry = table->entries;
//     while (entry) {
//         printf("%s\t%s\t", entry->name, typeToString(entry->type));
        
//         if (entry->type == ARRAY_T || entry->type == PTR_T)
//             printf("%s\t", typeToString(entry->eleType));
//         else
//             printf("N/A\t");
        
//         printf("%d\t%d\t", entry->size, entry->offset);
        
//         // Print initial value based on type
//         if (entry->initialValue) {
//             switch (entry->type) {
//                 case INT_T:
//                     printf("%d", *(int*)entry->initialValue);
//                     break;
//                 case FLOAT_T:
//                     printf("%f", *(float*)entry->initialValue);
//                     break;
//                 case CHAR_T:
//                     printf("%c", *(char*)entry->initialValue);
//                     break;
//                 default:
//                     printf("N/A");
//             }
//         } else {
//             printf("NULL");
//         }
        
//         printf("\n");
//         entry = entry->next;
//     }
    
//     printf("\n");
// }
void printSymbolTable(SymbolTable *table) {
    printf("\n### Symbol Table: %s\n", table->name);
    printf("| Name     | Type        | Initial Value | Size | Offset | Nested Table   |\n");
    printf("|----------|-------------|---------------|------|--------|----------------|\n");
    
    SymbolEntry *entry = table->entries;
    while (entry) {
        printf("| %-8s | %-11s | ", entry->name, typeToString(entry->type));
        
        // Print initial value based on type
        if (entry->initialValue) {
            switch (entry->type) {
                case INT_T:
                    printf("%-13d | ", *(int*)entry->initialValue);
                    break;
                case FLOAT_T:
                    printf("%-13.1f | ", *(float*)entry->initialValue);
                    break;
                case CHAR_T:
                    printf("'%-12c | ", *(char*)entry->initialValue);
                    break;
                default:
                    printf("%-13s | ", "-");
            }
        } else {
            printf("%-13s | ", "-");
        }
        
        // Print size and offset
        printf("%-4d | %-6d | ", entry->size, entry->offset);
        
        
        // Print nested table info
        if (entry->nestedTable) {
            printf("ST(%-10s) |", entry->nestedTable->name);
        } else {
            printf("%-15s |", "null");
        }

        
        
        printf("\n");
        entry = entry->next;
    }
    
    printf("\n");
}

// Quad functions
void emitQuad(char *op, char *arg1, char *arg2, char *result) {
    quads[quadIndex].op = op ? strdup(op) : NULL;
    quads[quadIndex].arg1 = arg1 ? strdup(arg1) : NULL;
    quads[quadIndex].arg2 = arg2 ? strdup(arg2) : NULL;
    quads[quadIndex].result = result ? strdup(result) : NULL;
    quadIndex++;
}

void printQuads() {
    printf("\nQuad Array:\n");
    printf("Index\tOperator\tArg1\tArg2\tResult\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < quadIndex; i++) {
        printf("%d\t%s\t\t%s\t%s\t%s\n", i, 
               quads[i].op ? quads[i].op : "NULL",
               quads[i].arg1 ? quads[i].arg1 : "NULL",
               quads[i].arg2 ? quads[i].arg2 : "NULL",
               quads[i].result ? quads[i].result : "NULL");
    }
    
    printf("\n");
}
void printQuadsinstruction() {
    printf("\n## Generated 3-Address Code:\n\n");
    printf("```\n");
    
    char currentFunc[50] = "";
    for (int i = 0; i < quadIndex; i++) {
        // If we're seeing a function label (LABEL followed by func:), print Function header
        if (strcmp(quads[i].op, "LABEL") == 0 && strstr(quads[i].result, "func_") != NULL) {
            char funcName[50];
            sscanf(quads[i].result, "func_%s", funcName);
            printf("Function: %s\n", funcName);
            strcpy(currentFunc, funcName);
            continue;
        }
        
        // Print normal instruction with L prefix for labels
        printf("L%-3d: ", i);
        
        // Handle different quad formats based on operation
        if (strcmp(quads[i].op, "=") == 0) {
            printf("%s = %s\n", quads[i].result, quads[i].arg1);
        }
        else if (strcmp(quads[i].op, "+") == 0 || 
                 strcmp(quads[i].op, "-") == 0 ||
                 strcmp(quads[i].op, "*") == 0 ||
                 strcmp(quads[i].op, "/") == 0 ||
                 strcmp(quads[i].op, "%") == 0 ||
                 strcmp(quads[i].op, "&") == 0 ||
                 strcmp(quads[i].op, "|") == 0 ||
                 strcmp(quads[i].op, "^") == 0 ||
                 strcmp(quads[i].op, "<<") == 0 ||
                 strcmp(quads[i].op, ">>") == 0) {
            printf("%s = %s %s %s\n", quads[i].result, quads[i].arg1, quads[i].op, quads[i].arg2);
        }
        else if (strcmp(quads[i].op, "=[]") == 0) {
            printf("%s = %s[%s]\n", quads[i].result, quads[i].arg1, quads[i].arg2);
        }
        else if (strcmp(quads[i].op, "[]=") == 0) {
            printf("%s[%s] = %s\n", quads[i].result, quads[i].arg1, quads[i].arg2);
        }
        else if (strcmp(quads[i].op, "goto") == 0) {
            printf("goto L%s\n", quads[i].result);
        }
        else if (strcmp(quads[i].op, "if") == 0) {
            printf("if %s goto L%s\n", quads[i].arg1, quads[i].result);
        }
        else if (strcmp(quads[i].op, "ifFalse") == 0) {
            printf("ifFalse %s goto L%s\n", quads[i].arg1, quads[i].result);
        }
        else if (strstr(quads[i].op, "if") != NULL && strstr(quads[i].op, "goto") != NULL) {
            // Handle relational operations (if x relop y goto L)
            char relop[5];
            sscanf(quads[i].op, "if%s", relop);
            printf("if %s %s %s goto L%s\n", quads[i].arg1, relop, quads[i].arg2, quads[i].result);
        }
        else if (strcmp(quads[i].op, "param") == 0) {
            printf("param %s\n", quads[i].arg1);
        }
        else if (strcmp(quads[i].op, "call") == 0) {
            printf("%s = call %s, %s\n", quads[i].result, quads[i].arg1, quads[i].arg2);
        }
        else if (strcmp(quads[i].op, "return") == 0) {
            if (quads[i].arg1)
                printf("return %s\n", quads[i].arg1);
            else
                printf("return\n");
        }
        else if (strstr(quads[i].op, "=") == 0) {
            // Handle unary operations
            char unaryOp[20];
            sscanf(quads[i].op, "%s", unaryOp);
            printf("%s = %s %s\n", quads[i].result, unaryOp, quads[i].arg1);
        }
        else if (strcmp(quads[i].op, "=inttoreal") == 0) {
            printf("%s = float2int(%s)\n", quads[i].result, quads[i].arg1);
        }
        else if (strcmp(quads[i].op, "=realtoint") == 0) {
            printf("%s = int2float(%s)\n", quads[i].result, quads[i].arg1);
        }
        else {
            // Generic format for other operations
            printf("%s %s %s %s\n", 
                   quads[i].op ? quads[i].op : "", 
                   quads[i].arg1 ? quads[i].arg1 : "", 
                   quads[i].arg2 ? quads[i].arg2 : "", 
                   quads[i].result ? quads[i].result : "");
        }
    }
    
    printf("```\n");
}

int nextquad() {
    return quadIndex;
}

QuadList* makelist(int i) {
    QuadList *list = (QuadList*)malloc(sizeof(QuadList));
    list->index = i;
    list->next = NULL;
    return list;
}

QuadList* merge(QuadList *p1, QuadList *p2) {
    if (!p1) return p2;
    if (!p2) return p1;
    
    QuadList *temp = p1;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = p2;
    
    return p1;
}

void backpatch(QuadList *p, int i) {
    QuadList *temp = p;
    char index_str[10];
    sprintf(index_str, "%d", i);
    
    while (temp) {
        if (quads[temp->index].result == NULL) {
            quads[temp->index].result = strdup(index_str);
        }
        temp = temp->next;
    }
}

// Type checking and conversion functions
Type typecheck(Type type1, Type type2) {
    if (type1 == type2) 
        return type1;
    
    // Handle type conversions based on rules
    if ((type1 == INT_T && type2 == FLOAT_T) || (type1 == FLOAT_T && type2 == INT_T))
        return FLOAT_T;  // Promote to float
    
    if ((type1 == CHAR_T && type2 == INT_T) || (type1 == INT_T && type2 == CHAR_T))
        return INT_T;    // Promote to int
    
    if (type1 == PTR_T || type2 == PTR_T)
        return PTR_T;    // Pointer-related operations
    
    if (type1 == BOOL_T || type2 == BOOL_T)
        return BOOL_T;   // Logical operations
    
    return VOID_T;  // Incompatible types
}

char* convInt2Float(char *s) {
    SymbolEntry *temp = gentemp(currentTable, FLOAT_T);
    emitQuad("=inttoreal", s, NULL, temp->name);
    return temp->name;
}

char* convFloat2Int(char *s) {
    SymbolEntry *temp = gentemp(currentTable, INT_T);
    emitQuad("=realtoint", s, NULL, temp->name);
    return temp->name;
}

char* convChar2Int(char *s) {
    SymbolEntry *temp = gentemp(currentTable, INT_T);
    emitQuad("=chartoint", s, NULL, temp->name);
    return temp->name;
}

char* convInt2Char(char *s) {
    SymbolEntry *temp = gentemp(currentTable, CHAR_T);
    emitQuad("=inttochar", s, NULL, temp->name);
    return temp->name;
}

char* convBool2Int(char *s) {
    SymbolEntry *temp = gentemp(currentTable, INT_T);
    emitQuad("=booltoint", s, NULL, temp->name);
    return temp->name;
}

char* convInt2Bool(char *s) {
    SymbolEntry *temp = gentemp(currentTable, BOOL_T);
    emitQuad("=inttobool", s, NULL, temp->name);
    return temp->name;
}

// Helper functions
char* newLabel() {
    char *label = (char*)malloc(10);
    sprintf(label, "L%d", labelCount++);
    return label;
}

char* newTemp() {
    char *temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempVarCount++);
    return temp;
}

int sizeOfType(Type type) {
    switch (type) {
        case VOID_T: return 0;
        case CHAR_T: return 1;
        case INT_T: return 4;
        case FLOAT_T: return 8;
        case PTR_T: return 4;  // All pointers have same size
        case BOOL_T: return 1;
        case ARRAY_T: return 1;
        default: return 0;
    }
}

char* typeToString(Type type) {
    switch (type) {
        case VOID_T: return "void";
        case CHAR_T: return "char";
        case INT_T: return "int";
        case FLOAT_T: return "float";
        case PTR_T: return "ptr";
        case ARRAY_T: return "array";
        case FUNC_T: return "function";
        case BOOL_T: return "bool";
        default: return "unknown";
    }
}
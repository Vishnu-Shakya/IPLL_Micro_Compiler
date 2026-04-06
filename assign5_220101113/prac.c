#include <stdio.h>
#include <stdlib.h>
#include "prac.h"

int main(int argc, char* argv[]) {
    int token;
    
    // Check if a filename was provided
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    // Open the input file
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Cannot open input file %s\n", argv[1]);
        return 1;
    }
    
    // Set flex to read from input file
    yyin = input_file;
    FILE* output_file = fopen("output.txt", "w+");
    
    // Process tokens
    fprintf(output_file,"%-20s %-20s %-20s\n", "Token", "Lexeme", "Line No.");
    fprintf(output_file,"------------------------------------------------\n");
    
    while ((token = yylex())) {
        if (token == INVALID) {
            fprintf(output_file,"Error: Invalid token '%s' at line %d\n", yytext, yylineno);
            continue;
        }
        fprintf(output_file,"%-20s %-20s %-20d\n", get_token_name(token), yytext, yylineno);
    }
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}
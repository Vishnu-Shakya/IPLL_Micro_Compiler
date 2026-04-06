// Test file for nanoC lexical analyzer

/* This is a multi-line comment
   testing various lexical elements */

// Testing keywords
void int char if else for return

// Testing identifiers
variable123
_test
camelCase
UPPERCASE
mixed_Case_123

// Testing integer constants
42
+100
-999
0

// Testing character constants
'a'
'\n'
'\t'
'\''

// Testing string literals
"Hello, World!"
"Special chars: \n \t \\"
""

// Testing punctuators
[ ] ( ) { } -> & * + - / % ! ?
< > <= >= == != && || = : ; ,

// Testing expressions and statements
int main() {
    int x = -42;
    char c = 'Z';
    if (x > 0) {
        return 1;
    } else {
        return 0;
    }
}

// Testing invalid tokens
@ # $ `
/* This is a test file for micro C language
   It covers all lexical elements defined in the specification */

// Single-line comment test

// Testing keywords
void main() begin
    // Variable declarations with different types
    integer x;
    float y;
    char c;
    bool isTrue;
    
    // Testing initializers
    integer a = 10;
    float b = 3.14;
    char letter = 'A';
    bool flag = 1;
    
    // Testing arrays
    integer numbers[10];
    char name[20];
    
    // Testing expressions
    x = 5;
    y = 2.5;
    c = 'Z';
    
    // Testing arithmetic operations
    x = a + 5;
    y = b * 2.0;
    a = a / 2;
    a = a % 3;
    a = a - 1;
    
    // Testing relational operations
    if (x > 0) begin
        x = x + 1;
    end
    
    if (y <= 5.0) begin
        y = y * 2.0;
    end else begin
        y = y / 2.0;
    end
    
    // Testing logical operations
    if (x > 0 && y > 0) begin
        flag = 1;
    end
    
    if (x < 0 || y < 0) begin
        flag = 0;
    end
    
    if (!flag) begin
        flag = 1;
    end
    
    // Testing for loop
    for (x = 0; x < 10; x++) begin
      for(integer p=0; p<10;p=p+1) begin
         integer q=q+1;
         end
        numbers[x] = x * x;
    end
    
    // Testing conditional expression
    a = (x > y) ? x : y;
    
    // Testing function call
    printNumber(a);
    
    // Testing return statement
    return 0;
end

// Function definition test
void printNumber(integer num) begin
    // Function body
    return;
end

// Testing pointer operations
void swapValues(integer *a, integer *b) begin
    integer temp;
    temp = *a;
    *a = *b;
    *b = temp;
end

// Testing string literals
void printMessage() begin
    char *message = "Hello, micro C!";
    // Use of string literal
end
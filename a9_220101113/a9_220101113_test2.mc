// Test 2: Control flow structures
// Testing if-else, loops, and function calls

// Function declarations
int add(int a, int b);
float average(int x, int y, int z);

void main()
begin
    int a = 5, b = 10, c = 15;
    int result;
    
    // If-else statement
    if (a < b) 
    begin
        result = a;
    end 
    else 
    begin
        result = b;
    end
    
    // Nested if-else
    if (a > b) 
    begin
        if (a > c) 
        begin
            result = a;
        end 
        else 
        begin
            result = c;
        end
    end 
    else 
    begin
        if (b > c) 
        begin
            result = b;
        end 
        else 
        begin
            result = c;
        end
    end
    
    // While loop
    int i = 0;
    while (i < 10) 
    begin
        i = i + 1;
    end
    
    // Do-while loop
    int j = 10;
    do 
    begin
        j = j - 1;
    end while (j > 0);
    
    // For loop
    int sum = 0;
    for (i = 0; i < 5; i = i + 1) 
    begin
        sum = sum + i;
    end
    
    // Function calls
    result = add(a, b);
    float avg = average(a, b, c);
end

// Function definition
int add(int a, int b)
begin
    return a + b;
end

// Function with multiple parameters
float average(int x, int y, int z)
begin
    int sum = x + y + z;
    return sum / 3.0;
end
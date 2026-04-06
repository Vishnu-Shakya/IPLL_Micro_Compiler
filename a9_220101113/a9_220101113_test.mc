/* Test file 1: Basic Expressions and Declarations */
/* Tests variable declarations, simple assignments, and arithmetic expressions */
float d = 2.3;
int arr1[10];


int main() 
begin
    // Variable declarations with initializations
    int a = 10;
    int b = 5;
    float c = 2.5;
    char d = 'x';
    int arr[5];
    int *ptr;
    
    // Simple assignments
    ptr = &a;
    *ptr = 20;
    arr[0] = 1;
    arr[1] = 2;
    
    // Arithmetic expressions
    int result;
    result = a + b;
    result = a - b;
    result = a * b;
    result = a / b;
    result = a % b;
    result=arr[0]*arr[1];
    
    // Mixed type expressions
    float f_result;
    f_result = a + c;
    f_result = b * c;
    
    // Assignment with expressions
    arr[3] = b * 2;
    
    return 0;
    end

int factorial(int n) 
begin
    int result = 1;
    int i = 1;
    
    while (i <= n) begin
        result = result * i;
        i = i + 1;
    end
    
    return result;
end

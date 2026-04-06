To compile and run the program for intermediate code genration write following in terminal:

make

followed by :

./a9_220101107 < a9_220101107_test.mc > 220101107_quads1.out

This will create output file 220101107_quads1.out which consists of quad array, 3 Address code and symbol table for the test program a9_220101107_test.mc.

./a9_220101107 < a9_220101107_test2.mc > 220101107_quads2.out

This will create output file 220101107_quads2.out which consists of quad array, 3 Address code and symbol table for the test program a9_220101107_test2.mc.

I have tried to implement symbol table but there is some issue with functional paratmeters being declared in global symbol table rather than functional symbol table.
Also I have used int instead of integer

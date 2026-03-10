# Polynomial-Stack
A C++ program that stores polynomial expressions using a linked-list structure and supports stack-based operations. From a command file it reads in polynomials in the format +(int)x(int)-(int)x(int). When given a new polynomial, it is stored on top. It has several actions it can do with the polynomial. 
* **"print"** - prints the top polynomial.
* **"derive"** - takes the derivative of the top polynomial.
* **"pop"** - removes the top polynomial.
* **"rotc"** - rotates the coefficients in the polynomial.
* **"topcopy"** - makes a copy of the top polynomial.
* **"hiterm"** - prints the highest-degree term of the polynomial.
* **"loterm"** - prints the lowest-degree term of the polynomial.
* **"neg"** - negates the polynomial.
* **"size"** - tells the number of terms in the top polynomial.
* **"add"** - adds all the polynomials and clears the stack.
### Example:
```
+5x2-3x3+1x0
print
topcopy
derive
add
```

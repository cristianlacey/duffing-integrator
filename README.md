# Duffing Equation Integrator
## APC 524: HW1

## Description
Running "make" generates 3 executables that solve the duffing equation,
decomposed as a system of first-order differential equations in the form
x_dot = Ax + B. The integrator can solve *any* equation, not only the duffing
equation; simply replace the entries of A and B in duffing.c, along with n,
the number of dimensions of the state vector. Each executable solves the
equation using one of the following numerical methods:
- Euler
- 4th Order Runge-Kutta
- 2nd Order Adams-Bashforth

## Dependencies
- duffing.c
- euler.c
- rk4.c
- ab2.c
- integrator.h
- Makefile

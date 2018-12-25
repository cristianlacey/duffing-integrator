#include "integrator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calc_rhs(int n, double t, const double *x, double *Dx)
{
  /* System of equations in form, x_dot = Ax + B. A and B defined
     for specified duffing equation.*/
  double A[2][2] = {
    {       (0)       ,    (1)  },
    { (1-pow(x[0],2)) ,  (-0.2) }
  };
  double B[2] = { 0 , (0.3*cos(t)) };
  
  /* Calculate right hand side, f(x,t) for each component
     of state vector, in terms of x, A, and B. */
  for(int i = 0; i < n; i++)
    {
      Dx[i] = A[i][0]*x[0]+A[i][1]*x[1]+B[i];
    }

  return 0;
}

int main(int argc, char *argv[])
{
  /* Initialize n, dimension of state vector, dt, timestep, and
     steps, number of steps. */
  int n = 2;
  FuncPtr rhs = calc_rhs;
  double dt = atof(argv[1]);
  int steps = atof(argv[2]);

  int step_err;
 
  Integrator *integrator = integrator_new(n,dt,rhs);

  /* Initialize x and t.*/
  double t = 0;
  double x[2] = {0};

  /* Print initial conditions.*/
  printf("%15.8f",t);
  for(int i = 0; i < n; i++)
    {
      printf(" %15.8f",x[i]);
    }
  printf("\n");

  /* Iterate through steps, printing output along the way.*/
  for(int i = 0; i < steps; i++)
    {
      /*Call integrator_step() and check if it returns an error.*/
      if(step_err = integrator_step(integrator,t,x))
	{
	  return step_err;
	}

      t += dt;

      /*Print new step in specified format.*/
      printf("%15.8f",t);
      for(int i = 0; i < n; i++)
	{
	  printf(" %15.8f",x[i]);
	}
      printf("\n");
    }

  /* Free integrator and memory allocated to its fields */
  integrator_free(integrator);
  
  return 0;
}

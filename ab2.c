#include "integrator.h"
#include <stdio.h>
#include <stdlib.h>

struct integrator_t
{
  double *Dx;
  double dt;
  FuncPtr rhs;
  int n;
  double *Dx_prev;
  int is_first_iter;
};

int integrator_step(Integrator *integrator, double t, double *x)
{
  double dt = integrator->dt;
  double *Dx = integrator->Dx;
  FuncPtr rhs = integrator->rhs;
  int n = integrator->n;
  double *Dx_prev = integrator->Dx_prev;
  int is_first_iter = integrator->is_first_iter;
  int rhs_err;

  /*Calculate f(x,t) and check if it return an error.*/
  if(rhs_err = rhs(n,t,x,Dx))
    {
      return rhs_err;
    }

  if (is_first_iter)
    {
      /*Propogate each component of x with newly calculated Dx=f(x,t),
	according to Euler method. Save current Dx in Dx_prev for
	next iteration.*/
      for (int i = 0; i < n; i++)
	{
	  x[i] = x[i] + dt*Dx[i];
	  Dx_prev[i] = Dx[i];
	}
      integrator->is_first_iter = 0;
    }
  else
    {
      /*Propogate each component of x with newly calculated Dx=f(x,t),
	according to AB2 method. Save current Dx in Dx_prev for
	next iteration.*/
      for (int i = 0; i < n; i++)
	{
	  x[i] = x[i] + (3*dt/2)*Dx[i] - (dt/2)*Dx_prev[i];
	  Dx_prev[i] = Dx[i];
	}
    }

  return 0;
}

/*Allocates memory for Integrator structure and associated fields,
  then initializes fields and returns pointer to structure.*/
Integrator *integrator_new(int n, double dt, FuncPtr rhs)
{
  Integrator *integrator = malloc(sizeof(Integrator));

  integrator->Dx = malloc(sizeof(double)*n);
  integrator->dt = dt;
  integrator->rhs = rhs;
  integrator->n = n;
  integrator->Dx_prev = malloc(sizeof(double)*n);
  integrator->is_first_iter = 1;
  
  return integrator;
}

/* Frees fields and structure.*/
void integrator_free(Integrator *integrator)
{
  free(integrator->Dx);
  free(integrator->Dx_prev);
    
  free(integrator);
}



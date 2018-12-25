#include "integrator.h"
#include <stdio.h>
#include <stdlib.h>

struct integrator_t
{
  double *Dx;
  double dt;
  FuncPtr rhs;
  int n;
  double *k1;
  double *k2;
  double *k3;
  double *k4;
  double *xk2;
  double *xk3;
  double *xk4;
};

int integrator_step(Integrator *integrator, double t, double *x)
{
  double dt = integrator->dt;
  double *Dx = integrator->Dx;
  FuncPtr rhs = integrator->rhs;
  int n = integrator->n;
  double *k1 = integrator->k1;
  double *k2 = integrator->k2;
  double *k3 = integrator->k3;
  double *k4 = integrator->k4;
  double *xk2 = integrator->xk2;
  double *xk3 = integrator->xk3;
  double *xk4 = integrator->xk4;
  int rhs_err;

  /*Calculate f(x,t) and check if it return an error.*/
  if(rhs_err = rhs(n,t,x,Dx))
    {
      return rhs_err;
    }

  /*Save entries of f(x,t) to k1, then calculate xk2, the input to
    rhs() for calculating k2.*/
  for (int i = 0; i < n; i++)
    {
      k1[i] = Dx[i];
      xk2[i] = x[i] + (dt/2)*k1[i];
    }

  /*Calculate f(x+dt*k1/2,t+dt/2) and check if it return an error.*/
  if(rhs_err = rhs(n,t+(dt/2),xk2,Dx))
    {
      return rhs_err;
    }
  
  /*Save entries of f(x+dt*k1/2,t+dt/2) to k2, then calculate xk3, the
    input to rhs() for calculating k3.*/
  for (int i = 0; i < n; i++)
    {
      k2[i] = Dx[i];
      xk3[i] = x[i] + (dt/2)*k2[i];
    }
  
  /*Calculate f(x+dt*k2/2,t+dt/2) and check if it return an error.*/
  if(rhs_err = rhs(n,t+(dt/2),xk3,Dx))
    {
      return rhs_err;
    }

  /*Save entries of f(x+dt*k2/2,t+dt/2) to k3, then calculate xk4, the
    input to rhs() for calculating k4.*/
  for (int i = 0; i < n; i++)
    {
      k3[i] = Dx[i];
      xk4[i] = x[i] + dt*k3[i];
    }

  /*Calculate f(x+dt*k3,t+dt) and check if it return an error.*/
  if(rhs_err = rhs(n,t+dt,xk4,Dx))
    {
      return rhs_err;
    }

  k4 = Dx;


  /*Propogate each component of x according to RK4  method.*/
  for (int i = 0; i < n; i++)
    {
      x[i] = x[i] + (dt/6)*k1[i] + (dt/3)*(k2[i]+k3[i]) + (dt/6)*k4[i];
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
  integrator->k1 = malloc(sizeof(double)*n);
  integrator->k2 = malloc(sizeof(double)*n);
  integrator->k3 = malloc(sizeof(double)*n);
  integrator->k4 = malloc(sizeof(double)*n);
  integrator->xk2 = malloc(sizeof(double)*n);
  integrator->xk3 = malloc(sizeof(double)*n);
  integrator->xk4 = malloc(sizeof(double)*n);
  
  return integrator;
}

/* Frees fields and structure.*/
void integrator_free(Integrator *integrator)
{
  free(integrator->Dx);
  free(integrator->k1);
  free(integrator->k2);
  free(integrator->k3);
  free(integrator->k4);
  free(integrator->xk2);
  free(integrator->xk3);
  free(integrator->xk4);
    
  free(integrator);
}



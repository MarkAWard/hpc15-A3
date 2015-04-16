#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double residual_norm(double *u, int N, double inv_h_sq);

int main(int argc, char **argv) {

  int N, n, i, max_iter, DEBUG;
  double h, h_sq, inv_h_sq, eps, res, init_res; 
  double *u, *u_update;

  // Number of points in (0,1)
  N = atoi(argv[1]);
  // Max iterations or till convergence
  if ( argc >= 3 )
    max_iter = atoi(argv[2]);
  else
    max_iter = -1;
  // Debug printing
  if ( argc >= 4) 
    DEBUG = 1;
  else
    DEBUG = 0;

  // alloc and init to 0.0
  u        = (double *) calloc( sizeof(double), N+2);
  u_update = (double *) calloc( sizeof(double), N+2);

  // required constants
  h        = 1.0 / (N + 1);
  h_sq     = h * h;
  inv_h_sq = 1.0 / h_sq;

  // for testing convergence
  eps      = 10e-5;
  init_res = residual_norm(u, N, inv_h_sq);
  res      = init_res;

  int tid;
  //#pragma omp parallel default(shared) private(i)
  //  {
  tid = omp_get_thread_num();
  // begin iterations
  for ( i = 0; i != max_iter && (res / init_res) > eps; ++i ) {
    
    // jacobi update
#pragma omp parallel for
    for( n = 1; n <= N; n++ )
      u_update[n] = 0.5 * (h_sq + u[n-1] + u[n+1]);

    // copy back to u
#pragma omp parallel for
    for( n = 1; n <= N; n++ )
      u[n] = u_update[n];

    // compute residual error
    res = residual_norm(u, N, inv_h_sq);


    // debug - error should decrease
    if ( DEBUG && i % 20 == 0 && tid == 0){
      printf("%d: %f\n", i, res );
    }
  }
  //  }
  // debug - n: x, exact solution, approx solution
  if ( DEBUG ) {
    for( n = 0; n <= N+1 && n < 50; n++ )
      printf("%d: %f\t%f\t%f\n", n, n*(1./(N+1)), 0.5 * (n*(1./(N+1))) * (1 - (n*(1./(N+1)))), u[n]);
  }

  // print some info
  printf("Total iterations: %d\n", i);
  printf("Initial residual: %f\n", init_res);
  printf("Final residual: %f\n", res);
  printf("Residual decrease: %f\n", init_res - res);

  // free heap mem
  free(u);
  free(u_update);

  return 0;
}

double residual_norm(double *u, int N, double inv_h_sq) {

  double tmp, total = 0.0;
  int i;
  // sum the squared error
#pragma omp parallel for reduction(+:total) private(tmp)
  for ( i = 1; i <= N; i++ ) {
    tmp = 1 - ((2.0 * u[i] - u[i-1] - u[i+1]) * inv_h_sq);
    total += tmp * tmp;
  } 
  // sqrt it
  return sqrt(total);
}


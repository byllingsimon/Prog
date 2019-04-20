#include<stdio.h>
#include<math.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include<stdlib.h>
#include<gsl/gsl_multiroots.h>
#include"rootfunctions.h"
#include"lineqfunctions.h"

int main(int argc, char** argv){

// Exercise A
fprintf(stdout, "Exercise A has started\n" );
// A.1
fprintf(stdout, "The Newton's method for analytic Jacobian and back-tracking linesearch has been implemented.\n" );
fprintf(stdout, "We test the implementation by at first solving the system of equations A*x*y = 1 , exp(-x) + exp(-y) = 1 + 1/A, with A= 10000 \n" );

// We allocate the parameters
gsl_vector* x_rosen = gsl_vector_alloc(2);
gsl_vector* x_rosen2 = gsl_vector_alloc(2);
gsl_vector* x_lineq = gsl_vector_alloc(2);
gsl_vector* x_lineq2 = gsl_vector_alloc(2);
gsl_vector* x_himmel = gsl_vector_alloc(2);
gsl_vector* x_himmel2 = gsl_vector_alloc(2);
gsl_vector* functioncall = gsl_vector_alloc(6);

// We set start parameters
gsl_vector_set(x_lineq, 0, 0);
gsl_vector_set(x_lineq, 1, 1);

vector_print("We use initial point at x0 = ",x_lineq);

// We calculate

gsl_vector_set(functioncall, 0, 0);
int steplineq1 = newton_with_jacobian(&function_linear_equation_with_j, x_lineq, 1e-6,functioncall);
fprintf(stdout,"The Newton method used %i steps and %g functioncalls.\n",steplineq1,gsl_vector_get(functioncall,0));

// We find
vector_print("The symmetric solutions is supposed to be at  x = [9.1061,0.00010981] or [0.00010981,9.1061], and is found to be x = ",x_lineq);


//A.2
fprintf(stdout, "We furthermore test the implementation by finding the minimum of the Rosenbrock funciton, \n" );
// We calculate
gsl_vector_set(x_rosen, 0, 0);
gsl_vector_set(x_rosen, 1, 0);
vector_print("We use initial point at x0 = ",x_rosen);
gsl_vector_set(functioncall, 1, 0);
int steprosen1 = newton_with_jacobian(&function_rosenbrock_with_j, x_rosen, 1e-6,functioncall);
fprintf(stdout,"The Newton method used %i steps and %g functioncalls.\n",steprosen1,gsl_vector_get(functioncall,1));
vector_print("Solution is supposed to be x=[1,1] and found to be x = ",x_rosen);


// A.3
fprintf(stdout, "We also test the implementation by finding the minimum of the Himmelblau's funciton, \n" );
// We calculate
gsl_vector_set(x_himmel, 0, 1);
gsl_vector_set(x_himmel, 1, 1);
vector_print("We use initial point at x0 = ",x_himmel);
gsl_vector_set(functioncall,2,0);
int stephimmel1 = newton_with_jacobian(&function_himmel_with_j, x_himmel, 1e-6,functioncall);
fprintf(stdout,"The Newton method used %i steps and %g functioncalls.\n",stephimmel1,gsl_vector_get(functioncall,2));

vector_print("Solution is supposed to be one of four local minima at f(3.0,2.0)=0.0,f(−2.805118,3.131312)= 0.0, f(−3.779310,−3.283186)=0.0 or f(3.584428,-1.848126)=0.0, and found to be x = ",x_himmel);
fprintf(stdout, "However since this function do not have the symmetry of the others, we cannot be sure that this point is not a maximum. Since this gradient has two direction components, and therefore cant be reduced to a minima, unless one test the found value afterwards, or know the approximate location of the minima. \n" );
fprintf(stdout, "This concludes the first exercise.  \n \n \n" );

// Exercise B
fprintf(stdout, "Exercise B has started\n" );

fprintf(stdout, "The Newton's method for numerical calculation of the Jacobian and back-tracking linesearch has been implemented.\n" );
fprintf(stdout, "We test the implementation, by comparing with the results of the previously done analytical calculations.\n" );
double stepsize = 1e-3;
fprintf(stdout, "For all of these, we use the same start-values and a stepsize of %g \n",stepsize);
fprintf(stdout, "We start by calculating the system of linear equaitons.\n");

//For the linear equations we calculate:
// We set start parameters
gsl_vector_set(x_lineq2, 0, 0);
gsl_vector_set(x_lineq2, 1, 1);
gsl_vector_set(functioncall, 3, 0);
int steplineq2 = newton(&function_linear_equation, x_lineq2,stepsize, 1e-6,functioncall);
fprintf(stdout,"The Numercal method used %i steps and %g functioncalls.  \nCompared to the analytical of %i steps and %g functioncalls. \n",steplineq2,gsl_vector_get(functioncall,3),steplineq1,gsl_vector_get(functioncall,0));
vector_print("The symmetric solutions is supposed to be at  x = [9.1061,0.00010981] or [0.00010981,9.1061], and is found to be x =",x_lineq2);

fprintf(stdout, "Now we find the solution for the minimum of the Rosenbrock funciton.\n");

//For the Rosenbrock we calculate:
gsl_vector_set(x_rosen2, 0, 0);
gsl_vector_set(x_rosen2, 1, 0);
gsl_vector_set(functioncall, 4, 0);
int steprosen2 = newton(&function_rosenbrock, x_rosen2,stepsize, 1e-6,functioncall);
fprintf(stdout,"The Numercal method used %i steps and %g functioncalls.  \nCompared to the analytical of %i steps and %g functioncalls. \n",steprosen2,gsl_vector_get(functioncall,4),steprosen1,gsl_vector_get(functioncall,1));
vector_print("Solution is supposed to be x=[1,1] and found numerically to be x = ",x_rosen2);


//For the Himmelblau function we calculate:
gsl_vector_set(x_himmel2, 0, 1);
gsl_vector_set(x_himmel2, 1, 1);
gsl_vector_set(functioncall, 5, 0);
int stephimmel2 = newton(&function_himmel, x_himmel2,stepsize, 1e-6,functioncall);
fprintf(stdout,"The Numercal method used %i steps and %g functioncalls.  \nCompared to the analytical of %i steps and %g functioncalls. \n",stephimmel2,gsl_vector_get(functioncall,5),stephimmel1,gsl_vector_get(functioncall,2));

vector_print("Solution is supposed to be one of four local minima at f(3.0,2.0)=0.0,f(−2.805118,3.131312)= 0.0, f(−3.779310,−3.283186)=0.0 or f(3.584428,-1.848126)=0.0, and found to be x = ",x_himmel2);

fprintf(stdout,"We hereby see, that in most cases the analytic solver is the best. But since the numerical solver depends strongly on the start paramers and stepsize, one cound be able to find itself in a position, where a numerical solver might compensate in a lucky way, to reduce the step size.  \n");
fprintf(stdout,"At last a comparison must be made with the built-in GSL functions. Theese calculations are started. \n");

// We call the GSL rootfinder, for comparison on the number of steps.
// This is done through a simple procedure of calling the GSL multirootfunction from the exercise on multiroots in the first part of the course.

// For the system of linear equations
double xlin = 0;
double ylin = 1;
double *px = &xlin;
double *py = &ylin;
gslroot_lin(px,py);

// For the Rosenbrock function
double xros = 0;
double yros = 0;
double *pxros = &xros;
double *pyros = &yros;
gslroot_rosen(pxros,pyros);

// For the Himmelblau function
double xhim = 1;
double yhim = 1;
double *pxhim = &xhim;
double *pyhim = &yhim;
gslroot_himmel(pxhim,pyhim);


fprintf(stdout,"To compare we find, that the GSL-multiroot functions is doing more steps than our functions, in order to find the correct value. However, the GSL functions are modified and optimized for the platfor. This gives the result that the functioncalls will be reduced, but sometimes make the stepnumber go higher instead. Therefore even thought it uses more steps, it might be way faster, and could be further optimized using a designated type instead of the gsl_multiroot_fsolver_hybrids \n");


fprintf(stdout,"With a comparison to the GSL routines, and the implementation of the numerical solver for the Jacobian, exercise B is hereby concluded.\n \n ");


// Exercise C
fprintf(stdout, "Exercise C has started\n" );



// We free the parameters

gsl_vector_free(x_lineq);
gsl_vector_free(x_lineq2);
gsl_vector_free(x_rosen);
gsl_vector_free(x_rosen2);
gsl_vector_free(x_himmel);
gsl_vector_free(x_himmel2);
gsl_vector_free(functioncall);
 return 0;
}
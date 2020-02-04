#include "stdio.h"
#include <math.h>
const int N = 10000;
double f(double y, double a, double b){
	double ret = 2*a*sqrt((1-(y-b)*(y-b)/b/b));
	return ret;
}
void trapezoidal_integral(double depth, int n, double width, double height, double length, double* integral_result){
	double delta = depth / n;
	double a=width/2, b = height/2;
	double sum= 0;
	for (register int i = 0 ; i < n ; i++){
		if (!i) sum += f(i*delta,a,b);
		else if (i==N-1) sum += f(i*delta,a,b);
		else sum += 2 * f(i*delta,a,b);
	}

	*integral_result = delta/2 * sum ;
	return;
}
int main(int argc, char const *argv[]){
	double w,h,l,d;
	double integral_result;
	printf("Enter the width of the tank (in meters): ");
	scanf("%lf",&w);
	printf("Enter the height of the tank (in meters): ");
	scanf("%lf",&h);
	printf("Enter the length of the tank (in meters): ");
	scanf("%lf",&l);
	printf("Enter the specific depth on the measuring stick (in centimeters): ");
	scanf("%lf",&d);
	d/=100;
	trapezoidal_integral(d,N,w,h,l,&integral_result);
	printf("Depth %.2lf cm : Volume %.2lf cubic meters\n",100*d,integral_result*l );

	return 0;
}
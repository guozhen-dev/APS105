#include <stdio.h>
#include <math.h>
int main(int argc, char const *argv[])
{
	int P, D ,term;
	double rate,M;
	printf("Enter the purchase price P: ");
	scanf("%d",&P);
	printf("Enter the amount of down payment D: ");
	scanf("%d",&D);
	printf("Enter the finance term (in months): ");
	scanf("%d",&term);
	printf("Enter the monthly interest rate (in percent): ");
	scanf("%lf",&rate);
	rate /= 100;
	M = ((P-D)*rate*pow(1+rate,term))/(pow(1+rate,term)-1);
	printf("The monthly payment is: %.2lf\n", M);
	return 0;
}
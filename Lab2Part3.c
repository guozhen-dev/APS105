//Name : Guozhen Ding (1005760749)
/*
 * Lab Submission for APS105H1
 * Input : The purchase price P, down payment D, and the finance term 'term'
 * Output : The monthly payment
 * Assumption : All input number is vaild and the result is in the range of 'double' \
 * 		and the P D term is in the range of int 
 */

#include <stdio.h>
#include <math.h>
int main(int argc, char const *argv[])
{
	//init the variables 
	int P, D ,term;
	double rate,M;

	//instruct the user to input all data needed 
	printf("Enter the purchase price P: ");
	scanf("%d",&P);
	printf("Enter the amount of down payment D: ");
	scanf("%d",&D);
	printf("Enter the finance term (in months): ");
	scanf("%d",&term);
	printf("Enter the monthly interest rate (in percent): ");
	scanf("%lf",&rate);

	//do calc and output the ans
	rate /= 100;
	M = ((P-D)*rate*pow(1+rate,term))/(pow(1+rate,term)-1);
	printf("The monthly payment is: %.2lf\n", M);
	return 0;
}

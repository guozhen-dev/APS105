#include <stdio.h>
#include <math.h>

double tot_int=0;
const double eps = 1e-4;
double owedAmount(double interest, double owedFromPre, double Purchase, double Payment){
	double ret;
	if (owedFromPre > 0 ){
		if (owedFromPre*(1+interest) + Purchase - Payment > 0 ){
			ret = (owedFromPre*(1+interest) + Purchase*(1+interest) - Payment);
			tot_int += (owedFromPre+Purchase)*interest;
		} else {
			ret = 0 ;
			tot_int += owedFromPre*interest;
		}
	} else {
		ret = Purchase - Payment > 0 ? (Purchase - Payment)*(1+interest)  : 0;
		tot_int += ((Purchase - Payment)>0?(Purchase - Payment):0) * interest;
		// printf("tot_int = %lf\n", tot_int);
	}
	// ret = owedFromPre + Purchase +((owedFromPre + Purchase)*interest) - Payment < 0 ? 0 : owedFromPre + Purchase +((owedFromPre + Purchase)*interest) - Payment;
	return ret; 
}

int main(int argc, char const * argv[]){
	double last_owe,last_last_owe, payPM, purPM, interest,tot;
	long long  N;
	printf("Enter amount already owed on card: ");
	scanf("%lf",&last_owe);
	printf("Enter purchase amount per month: ");
	scanf("%lf",&purPM);
	printf("Enter payment amount per month ");
	scanf("%lf",&payPM);
	printf("Enter yearly interest rate as percent: ");
	scanf("%lf",&interest);
	interest/=1200;
	printf("Enter number of months to consider: ");
	scanf("%lld",&N);
	tot = last_owe;
	// tot_int = last_owe * interest;
	for (int i = 0; i < N; i++){
		// printf("%lf %lf %lf %lf ", interest,last_owe,purPM,payPM);
		// tot_int += last_owe*interest;
		last_last_owe = last_owe;
		last_owe = owedAmount(interest,last_owe,purPM,payPM);
		// tot_int += last_owe+payPM-purPM-last_last_owe;
		// printf("%lf %lf %lf\n\n", last_owe , last_last_owe , tot_int);
	}
	printf("Total purchased value: %.2lf\n", N*purPM+tot );
	printf("Total interest charges: %.2lf\n", tot_int );
}
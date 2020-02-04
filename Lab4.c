/* Name : Guozhen Ding (1005760749)
 * Lab Submission for APS105H1
 * Input : The amount already owed on card,purchase amount per month,payment amount per month, \
 *         Enter yearly interest rate as percent, number of months to consider
 * Output : Total purchased value: & Total interest charges:
 * Assumption : All the input from the user is positive value and the months is an interger.
 */
#include <stdio.h>
#include <math.h>

double tot_int=0;
const double eps = 1e-4;								// declare global vars and constant


inline double owedAmount(double interest, double owedFromPre, double Purchase, double Payment){
	register double ret;
	if (owedFromPre > 0 ){
		if (owedFromPre*(1+interest) + Purchase - Payment > 0 ){
			ret = (owedFromPre*(1+interest) + Purchase*(1+interest) - Payment);
		} else {
			ret = 0 ;
		}
		tot_int += (owedFromPre+Purchase)*interest;
	} else {
		ret = Purchase - Payment > 0 ? (Purchase - Payment)*(1+interest)  : 0;
		tot_int += ((Purchase - Payment)>0?(Purchase - Payment):0) * interest;
	}
	return ret; 
}     													// owed money process function 

int main(int argc, char const * argv[]){

	//get user input 
	double last_owe,last_last_owe, payPM, purPM, interest,tot;
	long long  N;
	printf("Enter amount already owed on card: ");
	scanf("%lf",&last_owe);
	printf("Enter purchase amount per month: ");
	scanf("%lf",&purPM);
	printf("Enter payment amount per month: ");
	scanf("%lf",&payPM);
	printf("Enter yearly interest rate as percent: ");
	scanf("%lf",&interest);
	interest/=1200;
	printf("Enter number of months to consider: ");
	scanf("%lld",&N);

	//iterative call the function 
	tot = last_owe;
	for (register int i = 0; i < N; i++){
		last_last_owe = last_owe;
		last_owe = owedAmount(interest,last_owe,purPM,payPM);
	}

	//Output the answer.
	printf("Total purchased value: %.2lf\n", N*purPM+tot );
	printf("Total interest charges: %.2lf\n", tot_int );
}
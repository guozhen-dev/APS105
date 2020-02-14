/* Name : Guozhen Ding (1005760749)
 * Lab Submission for APS105H1
 * Input : Two integers for calc
 * Output : the m and p s.t. m*p = n , m+p = q
 * Assumption : All the input from the user is positive value.
 */
#include <stdio.h>
#include <stdlib.h>	

void getPairDivisor(int n , int q , int* mAddress, int* pAddress){  //function of calc
	for(int i = 0 ; i < q ; i++){
		if(i * (q-i)==n) {
			*mAddress = i; 
			*pAddress = q-i;
			return ;
		}
	}
	printf("The program could not find any pair divisors for these inputs");
	exit(0);
}
int main(int argc, char const *argv[]){
	int n,q,m,p;
	//get user input 
	printf("Please enter an input number n: ");
	printf("Please enter a query number q: ");
	scanf("%d %d",&n,&q);
	
	//call the function to do calc 
	getPairDivisor(n,q,&m,&p);
	
	//output the answer
	printf("m = %d, p = %d, m*p = %d, and m+p = %d\n", m , p , m*p, m+p);
	return 0;
}

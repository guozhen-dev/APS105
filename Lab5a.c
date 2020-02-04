#include <stdio.h>

void getPairDivisor(int n , int q , int* mAddress, int* pAddress){
	for(int i = 0 ; i < q ; i++){
		if(i * (q-i)==n) {
			*mAddress = i; 
			*pAddress = q-i;
			return ;
		}
	}
	printf("The program could not find any pair divisors for these inputs\n");
	exit(0);

}
int main(int argc, char const *argv[]){
	int n,q,m,p;
	printf("Please enter an input number n:");
	printf("Please enter a query number q:");
	scanf("%d %d",&n,&q);
	getPairDivisor(n,q,&m,&p);
	printf("m = %d, p = %d, m*p = %d, and m+p = %d\n", m , p , m*p, m+p);
	return 0;
}
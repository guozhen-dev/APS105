#include <stdio.h>
#include <string.h>
#include "Lab6.h"
void printline(long long  x){
	for (long long i = 0 ; i< 2*x-1 ; i++){
		putchar('-');
	}
	puts("");
}
int main(int argc, char const *argv[])
{
	// freopen ("in","r",stdin);
	long long r,c;
	double p;
	printf("Enter the number of rows: \nEnter the number of columns: \nEnter the probability p value: \n");
	scanf("%lld %lld %lf",&r,&c,&p);
	int ** mapp = (int ** )malloc( sizeof (int * ) * (r+2));
	for  (register long long  i = 0 ; i < r + 2 ; i ++){
		mapp[i] = (int * ) malloc (sizeof (int ) * (c+2));
	}
	for (register long long i = 0 ; i < r + 2 ; i++){
		for (register long long j = 0 ; j < c + 2 ; j++ ){
			mapp[i][j] = 0;
		}
	}
	printline(c);
	for ( register long long  i = 1; i < r + 1 ; i++){
		for (register long long  j = 1 ; j < c+1 ; j++){
			mapp[i][j] = rand()>p ? 0 : 1;
			printf("%c ",mapp[i][j]?'*':'.');
		}
		puts("");
	}
	printline(c);
	for ( register long long  i = 1; i < r + 1 ; i++){
		for (register long long  j = 1 ; j < c+1 ; j++){
			if (mapp[i][j]) putchar('*'),putchar(' ');
			else {
				printf("%d ", mapp[i-1][j-1]+mapp[i-1][j]+mapp[i-1][j+1]+mapp[i][j-1]+mapp[i][j+1]+mapp[i+1][j-1]+mapp[i+1][j]+mapp[i+1][j+1]);
			}
		}
		puts("");
	}



	return 0;
}
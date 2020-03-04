#include <stdio.h>
#include <string.h>
#include "Lab6.h"

const move[3]={-1,0,1};
long long r,c;
double p;
void pr_number(int i , int j , int mapp[]){
	int sum = 0 ;
	for (int k = 0 ; k < 3; k++){
		for (int l = 0 ; l < 3 ; l++){
			if ((!i && !k) || (!j && !l) || (i==r-1 && k==2)||(j==c-1 && l==2) || (k==1 && l==1)) continue; 
			sum += ( mapp[i+move[k]] >> (c-(j+move[l])-1) )%2;
		}
	}
	printf("%d ",sum);
}

int main(int argc, char const *argv[])
{
	// freopen("in","r",stdin);
	printf("Enter the number of rows: Enter the number of columns: Enter the probability p value: ");
	scanf("%lld %lld %lf", &r, &c, &p);
	int mapp[0x7ffff] = {0,};
	for (register int i = 0; i < 2*c-1 ; i++) putchar('-');
	putchar('\n');
	for (register int i = 0; i < r ; i++){
		for (register int j = 0 ; j < c ; j++){
			int result = rand() < p ? 1 : 0;
			if (result) putchar('*'),putchar(' '); else putchar('.'),putchar(' ');
			mapp[i] += result<<(c-j-1) ;
		}
		putchar('\n');
	}
	for (register int i = 0; i < 2*c-1 ; i++) putchar('-');
	puts("\n");
	for (int i = 0 ; i < r; i++){
		for (int j = 0 ; j < c ; j++){
			if ((mapp[i]>>(c-j-1)) % 2) {
				putchar('*'),putchar(' ');
				continue;
			}else{
				pr_number(i,j,mapp);
			}

		}
		puts("");
	}
	for (register int i = 0; i < 2*c-1 ; i++) putchar('-');
	return 0;
}

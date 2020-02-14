#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	srand(time(0));
	long long r,c;
	double p;
	printf("Enter the number of rows:\nEnter the number of columns:\nEnter the probability p value:\n");
	scanf("%lld %lld %lf", &r, &c, &p);
	int mapp[0x7ffff] = {0,};
	for (register int i = 0; i < 2*c-1 ; i++) putchar('-');
	puts("");
	for (register int i = 0; i < r ; i++){
		for (register int j = 0 ; j < c ; j++){
			int result = rand()/(double)RAND_MAX > p ? 1 : 0;
			if (result) putchar('*'),putchar(' '); else putchar('.'),putchar(' ');
			mapp[i] += result<<(c-j) ;
		}
		puts(' ');
	}
	for (register int i = 0; i < 2*c-1 ; i++) puts("-");
	puts("\n");
	return 0;
}
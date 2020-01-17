#include "stdio.h"

int main(int argc, char const *argv[])
{
	
	int input;
	scanf("%d",&input);
	int firstDigit = input / 1000;
	input -= firstDigit*1000;
	int secondDigit = input / 100;
	input -= secondDigit * 100;
	int thirdDigit = input / 10 ;
	input -= thirdDigit * 10 ;
	int ans = input * 1000 + firstDigit + (9 - secondDigit) * 100 + (9 - thirdDigit) * 10 ;
	printf("%04d\n", ans);
	

}
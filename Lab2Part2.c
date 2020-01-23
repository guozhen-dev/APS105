//Name : Guozhen Ding (1005760749)
/*
 * Lab Submission for APS105H1 
 * Input : The encrypted 4-digit combination
 * Output : The origin code for the safe using the give change method 
 * Assumption : All the input from the user is a 4-digit number 
 */
#include <stdio.h>

int main(int argc, char const *argv[])
{
	// Get input from user 
	int input;
	printf("Enter an encrypted 4-digit combination:");
	scanf("%d",&input);
	
	//Seperate the four digit from the input value
	int firstDigit = input / 1000;
	input -= firstDigit*1000;
	int secondDigit = input / 100;
	input -= secondDigit * 100;
	int thirdDigit = input / 10 ;
	input -= thirdDigit * 10 ;
	
	//re-combine the 4 digit and output to user 
	int ans = input * 1000 + firstDigit + (9 - secondDigit) * 100 + (9 - thirdDigit) * 10 ;
	printf("The real combination is: %04d\n", ans);
	

}

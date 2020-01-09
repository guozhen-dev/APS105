#include <stdio.h>

int main(int argc, char const *argv[]){
	int inputNumber1,inputNumber2,inputNumber3; //init the variables
	printf("Enter First Number: ");
	scanf("%d",&inputNumber1);
	printf("Enter Second Number: ");
	scanf("%d",&inputNumber2);
	printf("Enter Third Number: ");
	scanf("%d",&inputNumber3); //read in the three numbers
	printf("Sum: %d \n", inputNumber1+inputNumber2+inputNumber3);// calc and print the sum
	printf("First negated: %d \n", -1*inputNumber1); //calc and print the neg of number 1
	printf("After Number 2: %d \n", inputNumber2 + 1);//calc and print the next number of number 2
	printf("Product of Number 2 and Number 3: %d \n", inputNumber2 * inputNumber3); // calc and print the n2 * n3
	return 0; 
}

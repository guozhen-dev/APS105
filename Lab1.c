//Name : Guozhen Ding (1005760749)
/*
 * Lab Submission for APS105H1 
 * Input : The numbers from the user 
 * Output : Some strings and the calculation results of some operations
 * Assumption : All the input from the user is vaild 
 * Goal : Test the simple calcuation and I/O of C language 
 */
#include <stdio.h>
int main(int argc, char const *argv[]){
	int inputNumber1, inputNumber2, inputNumber3; //init the variables
	

	printf("Enter First Number: "); 
	// Give out instructions to the user
	scanf("%d",&inputNumber1);      
	// read in the 1st number
	printf("Enter Second Number: ");
	// Give out instructions to the user
	scanf("%d",&inputNumber2);      
	// Read in the second number
	printf("Enter Third Number: "); 
	// Give out instructions to the user
	scanf("%d",&inputNumber3); 	
	//read in the three numbers
	

	printf("Sum: %d \n", inputNumber1 + inputNumber2 + inputNumber3);	// calc and print the sum
	printf("First negated: %d \n", -1 * inputNumber1 ); 	//calc and print the neg of number 1
	printf("After Number 2: %d \n", inputNumber2 + 1 );//calc and print the next number of number 2
	printf("Product of Number 2 and Number 3: %d \n", inputNumber2 * inputNumber3 ); // calc and print the n2 * n3
	return 0;  			// return 0 
}
